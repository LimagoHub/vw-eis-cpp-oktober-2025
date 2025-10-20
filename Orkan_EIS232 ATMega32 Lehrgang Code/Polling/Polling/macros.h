/*
 * macros.h
 *
 * Created: 14.10.2025 08:27:38
 *  Author: Rechner Nr. 4
 */ 


#ifndef MACROS_H_
#define MACROS_H_

#define SET_BIT(BYTE,BIT) BYTE|=(1<<BIT)
#define CLEAR_BIT(BYTE,BIT) BYTE&=~(1<<BIT)
#define TOGGLE_BIT(BYTE,BIT) BYTE^=(1<<BIT)
#define GET_BIT(BYTE,BIT) (BYTE&(1<<BIT))

#endif /* MACROS_H_ */