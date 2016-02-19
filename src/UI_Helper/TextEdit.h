/*
 * TextEdit.h
 *
 *  Created on: 2.2.2016
 *      Author: krl
 */

#ifndef TextEdit_H_
#define TextEdit_H_

#include "../Protocol/PropertyEdit.h"
#include "../LCD/LiquidCrystal.h"
#include "../UI_Helper/TextEdit.h"
class TextEdit:public PropertyEdit {
public:
	TextEdit(LiquidCrystal& lcd_, std::string mode, std::string modeExplain);
	virtual ~TextEdit();
	void increment();
	void decrement();
	void accept();
	void cancel();
	void goBack();
	void setFocus(bool focus);
	void display();
	//void add(IntegerEdit *blabla){};
private:
	void displayEditValue();
	LiquidCrystal& lcd;
	std::string mode;
	std::string modeExplain;
	bool focus;
	int current;
};

#endif /* TextEdit_H_ */
