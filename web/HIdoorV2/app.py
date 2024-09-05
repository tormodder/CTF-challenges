from flask import Flask, request, jsonify, render_template, url_for, redirect
from flask_sqlalchemy import SQLAlchemy
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///users.db'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db = SQLAlchemy(app)

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(50), unique=True, nullable=False)
    password_hash = db.Column(db.String(128), nullable=False)
    is_admin = db.Column(db.Boolean, default=False)

    def set_password(self, password):
        self.password_hash = generate_password_hash(password)

    def check_password(self, password):
        return check_password_hash(self.password_hash, password)

def setup_database():
    db.create_all()

    # setup admin user
    admin_user = User.query.filter_by(username='admin').first()
    if not admin_user:
        admin = User(username='admin', is_admin=True)
        admin.set_password('ecZK1D6tP8fC8p2')
        db.session.add(admin)

    db.session.commit()

# push context manually to app
with app.app_context():
    setup_database()

@app.route('/')
def home():
    return render_template('portal.html')

@app.route('/register', methods=['GET','POST'])
def register():
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')

        if User.query.filter_by(username=username).first():
            return jsonify({"error": "Username already exists"}), 400

        new_user = User(username=username)
        new_user.set_password(password)
        db.session.add(new_user)
        db.session.commit()
        return jsonify({"message": "User created successfully"}), 201
    return render_template('register.html')

@app.route('/login', methods=['GET', 'POST'])
def login():
    if request.method == 'POST':
        username = request.form.get('username')
        password = request.form.get('password')
        user = User.query.filter_by(username=username).first()
        if user and user.check_password(password):
            # Render the redirection page with the user's ID
            return render_template('redirect.html', user_id=user.id)
        else:
            return "Invalid username or password", 401
    return render_template('login.html')

@app.route('/profile', methods=['POST'])
def profile():
    user_id = request.form.get('user_id')
    if not user_id:
        return "No user ID provided", 400
    user = User.query.get(user_id)
    if user:
        return render_template('profile.html', user=user)
    else:
        return "User not found", 404

    
if __name__ == "__main__":
    app.run("0.0.0.0", port=6788)
