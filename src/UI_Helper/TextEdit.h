/*
 * TextEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef TEXTEDIT_H_
#define TEXTEDIT_H_

#include "../Protocol/PropertyEdit.h"
#include "../LCD/LiquidCrystal.h"
#include <string>

class TextEdit:public PropertyEdit {
public:
	TextEdit(LiquidCrystal& lcd_, std::string mode, std::string modeExplain);
	virtual ~TextEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void setFocus(bool focus);
	void display();
	string name();
private:
	void save();
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string mode;
	std::string modeExplain;
	int value;
	int edit;
	bool focus;
};

#endif /* TEXTEDIT_H_ */
