/** @file
    @brief module that get and generate json files
*/

#ifndef CONVERT_H
#define CONVERT_H

#include <QString>

/**
    @brief get info about server
    @returns json string with server info
*/
QString getServerInfo();

/**
    @brief remove item from list by value
    @returns json string of favourite movie characters
*/
QString getFavourites();

/**
    @brief get json object with current id
    @param _id - value for check in json
    @returns string of json object with this id
*/
QString getIdObject(QString _id);

/**
    @brief get json array with current name
    @param _name - value for check in json
    @returns string of json array of objects with this names
*/
QString getNameObjects(QString _name);

/**
    @brief get number of movie characters written in json
    @returns number of favourites
*/
int getFavouritesSize();

/**
    @brief creates a json object from file with name, size and it's data
    @param nameOfFile - path to file
    @returns string of json object with info about file
*/
QString createDataJson(QString nameOfFile);

/**
    @brief creates a json object from file with info about numbers on odd positions
    @param nameOfFile - path to file
    @returns string of json object with info about numbers in file
*/
QString createDataNumbersJson(QString nameOfFile);

#endif // CONVERT_H
