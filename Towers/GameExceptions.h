///////////////////////////////////////////////////////////
///// Towers! game - Game Exception
///////////////////////////////////////////////////////////

#pragma once

// headers
#include<iostream>
#include<stdexcept>
#include<string>

// exception if something went wrong while creating world game
class FailLoadMap : public std::exception {
public:
	FailLoadMap(const std::string text) { ErrorMassage += text; }
	const char* what() const noexcept override { return ErrorMassage.c_str(); }
private:
	std::string ErrorMassage = "Error: ";
};
