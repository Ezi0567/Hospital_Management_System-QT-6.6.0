#ifndef GLOBALVAR_H
#define GLOBALVAR_H
#include<QString>
extern QString loggedindocemail;
extern QString loggedindocname;
extern QString loggedinstaffemail;
extern QString loggedinstaffname;
extern QString day; //For day of appointment to be set by staff
extern QString tim; //For time of appointment to be set by staff
extern QString docname; //For name of doctor of appointment to be set by staff
extern QString patname; //For name of patient of appointment to be set by staff
extern QString department; //For name of department of appointment to be set by staff
extern int doccount; //For checking number of doctors added as item in the combobox_2 of appointment section
extern double stlogint; //stafflogin time record
extern double stlogoutt;//staff logout time record
extern double dclogint;//doctor login time record
extern double dclogoutt;//doctor logout time record
extern QString patcode;
#endif // GLOBALVAR_H
