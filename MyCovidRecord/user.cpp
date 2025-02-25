#include "user.h"
//#include "mainwindow.h"
#include "database.h"
#include <iostream>
#include <QMessageBox>

User::User()
{
    isLoggedIn = false;
    
}

// method to create a new user
void User::createUser(std::string firstName, std::string lastName, std::string email, std::string password, std::string dateOfBirth, std::string NHI, bool admin) {
    this->firstName = firstName;
    this->lastName = lastName;
    this->email = email;
    this->password = password;
    this->dateOfBirth = dateOfBirth;
    this->NHI = NHI;
    this->admin = admin;

    this->isLoggedIn = true;
    
    // store user details in database
    database *db = new database();
    db->databaseConnect();
    db->addUser(firstName, lastName, email, password, dateOfBirth, NHI, admin);


}

bool User::loginUser(std::string email, std::string password) {
    database *db = new database();
    db->databaseConnect();
    userID = db->checkUser(email, password);

    if (userID != -1) {
        this->isLoggedIn = true;
        this->email = email;
        std::vector<std::string> userDetails = db->getUserDetails(userID);
        this->firstName = userDetails[1];
        this->lastName = userDetails[2];
        this->dateOfBirth = userDetails[4];
        this->NHI = userDetails[5];
        this->admin = userDetails[6] == "1" ? true : false;

        this->vaccineRecord = db->getVaccineRecord(userID);
        this->testResults = db->getTestRecord(userID);


        return true;
    } else {
        QMessageBox::warning(nullptr, "Login Failed", "Incorrect email or password");
        this->isLoggedIn = false;
        return false;
    }


    // get user details from database
    // set user details to this object
    
}

void User::addVaccine(std::string vaccineName, std::string date) {
    vaccineRecord[vaccineName] = date;
}

void User::addTestResult(std::string date, bool result) {
    testResults[date] = result;
}

void User::logoutUser() {
//    this->isLoggedIn = false;
}

User::~User()
{
}
