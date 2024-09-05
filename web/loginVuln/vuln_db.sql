CREATE DATABASE IF NOT EXISTS vuln_db;
USE vuln_db;

CREATE TABLE users (
    username VARCHAR(50),
    password VARCHAR(50)
);

INSERT INTO users (username, password) VALUES ('admin', 'swordPassFishesAndLongWords73843908');
