


// code made a elik7777
// company R0B0C0DE


#ifndef SEVEN_SEGMENT_DISPLAY_H
#define SEVEN_SEGMENT_DISPLAY_H
#include <Arduino.h>
extern int A, B, C, D, E, F, G, TENS, ONES, H;
void clearDisplaySegment() {
    digitalWrite(A, LOW);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);
    digitalWrite(G, LOW);
    digitalWrite(H, LOW);
    digitalWrite(TENS, LOW);
    digitalWrite(ONES, LOW);
}
void displayDigitSegment(int digit, bool isTens, bool showDot = false) {
    clearDisplaySegment();
    if (isTens) {
        digitalWrite(TENS, LOW);
        digitalWrite(ONES, HIGH);
    } else {
        digitalWrite(TENS, HIGH);
        digitalWrite(ONES, LOW);
    }
    digitalWrite(H, showDot ? HIGH : LOW);
    switch(digit) {
        case 0:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            break;
            
        case 1:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
            
        case 2:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, HIGH);
            break;
            
        case 3:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, HIGH);
            break;
            
        case 4:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
            
        case 5:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, LOW);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
            
        case 6:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
            
        case 7:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
            
        case 8:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
            
        case 9:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, LOW);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
            
        default:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, HIGH);
            break;
    }
}



#endif