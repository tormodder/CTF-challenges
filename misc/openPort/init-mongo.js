db = new Mongo().getDB('secrets');
db.myCollection.insertOne({ dataEntry: 'CTFkom{connecting_is_the_hardest_part47153524}' });
