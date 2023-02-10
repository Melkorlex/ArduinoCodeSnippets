// In this file i desricbed which variables, instances & objects are necessary to connect Arduino with Nextion HMI

#ifndef INIT_H
#define INIT_H
#include Nextion.h

// Optional: Define the Page No. (makes easier to handle if you have a lot of pages)
#define PAGE_ID_MAINVIEW 0  // Main view 

// ############ 
// Declare a button object [page id:,component id:, component name: ]. 
// ############
// Main View
NexText     t0Mainview  = NexText(PAGE_ID_MAINVIEW,0,"t0"); // Text Object, on Page 0 für cmp t0
