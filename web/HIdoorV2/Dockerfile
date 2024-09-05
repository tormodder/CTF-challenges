# Use an official Python runtime as the parent image
FROM python:3.8-slim

# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY app.py /app/
COPY static/ /app/static/
COPY templates/ /app/templates/

# Install Flask and its dependencies
RUN pip install --trusted-host pypi.python.org flask
RUN pip install --trusted-host pypi.python.org Flask-SQLAlchemy

# Exposed prefered port
EXPOSE 6788

# Run the application when the container is started
CMD ["python", "app.py"]
