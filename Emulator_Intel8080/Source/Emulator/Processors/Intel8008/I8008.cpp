#include "Emulator/Processors/Intel8008/I8008.h"


I8008::I8008() : Processor(u8"Intel 8008") {

}
I8008::~I8008() {

}



Momento* I8008::SaveState() {
	return nullptr;
}
void     I8008::RestoreState(Momento* momento) {

}




void I8008::_NOP() {

}
void I8008::_HLT() {

}

//rotate
void I8008::_RLC() {

}
void I8008::_RAL() {

}
void I8008::_RRC() {

}
void I8008::_RAR() {

}

//returns
void I8008::_RET() {

}
void I8008::_RFC(){

}
void I8008::_RFS(){

}
void I8008::_RFZ(){

}
void I8008::_RFP(){

}
void I8008::_RTC(){

}
void I8008::_RTS(){

}
void I8008::_RTZ(){

}
void I8008::_RTP(){

}

//rst
void I8008::_RST0(){

}
void I8008::_RST1(){

}
void I8008::_RST2(){

}
void I8008::_RST3(){

}
void I8008::_RST4(){

}
void I8008::_RST5(){

}
void I8008::_RST6(){

}
void I8008::_RST7(){

}

//increment & decrement
void I8008::_INC(){

}
void I8008::_INB(){

}
void I8008::_INE(){

}
void I8008::_IND(){

}
void I8008::_INL(){

}
void I8008::_INH(){

}
void I8008::_DCC(){

}
void I8008::_DCB(){

}
void I8008::_DCE(){

}
void I8008::_DCD(){

}
void I8008::_DCL(){

}
void I8008::_DCH(){

}

void I8008::_ADI(){

}
void I8008::_ACI(){

}
void I8008::_SUI(){

}
void I8008::_SBI(){

}
void I8008::_NDI(){

}
void I8008::_XRI(){

}
void I8008::_ORI(){

}
void I8008::_CPI(){

}
void I8008::_LAI(){

}
void I8008::_LCI(){

}
void I8008::_LDI(){

}
void I8008::_LEI(){

}
void I8008::_LHI(){

}
void I8008::_LLI(){

}
void I8008::_LBI(){

}
void I8008::_LMI() {

}
//jumps
void I8008::_JMP(){

}
void I8008::_JFC(){

}
void I8008::_JFZ(){

}
void I8008::_JFS(){

}
void I8008::_JFP(){

}
void I8008::_JTC(){

}
void I8008::_JTZ(){

}
void I8008::_JTS(){

}
void I8008::_JTP(){

}

//calls
void I8008::_CAL(){

}
void I8008::_CFC(){

}
void I8008::_CFZ(){

}
void I8008::_CFS(){

}
void I8008::_CFP(){

}
void I8008::_CTC(){

}
void I8008::_CTZ(){

}
void I8008::_CTS(){

}
void I8008::_CTP(){

}

// inputs
void I8008::_INP0(){

}
void I8008::_INP1(){

}
void I8008::_INP2(){

}
void I8008::_INP3(){

}
void I8008::_INP4(){

}
void I8008::_INP5(){

}
void I8008::_INP6(){

}
void I8008::_INP7(){

}

// outputs
void I8008::_OUT0(){

}
void I8008::_OUT1(){

}
void I8008::_OUT2(){

}
void I8008::_OUT3(){

}
void I8008::_OUT4(){

}
void I8008::_OUT5(){

}
void I8008::_OUT6(){

}
void I8008::_OUT7(){

}
void I8008::_OUT8(){

}
void I8008::_OUT9(){

}
void I8008::_OUT10(){

}
void I8008::_OUT11(){

}
void I8008::_OUT12(){

}
void I8008::_OUT13(){

}
void I8008::_OUT14(){

}
void I8008::_OUT15(){

}
void I8008::_OUT16(){

}
void I8008::_OUT17(){

}
void I8008::_OUT18(){

}
void I8008::_OUT19(){

}
void I8008::_OUT20(){

}
void I8008::_OUT21(){

}
void I8008::_OUT22(){

}
void I8008::_OUT23(){

}
void I8008::_OUT24(){

}
void I8008::_OUT25(){

}
void I8008::_OUT26(){

}
void I8008::_OUT27(){

}
void I8008::_OUT28(){

}
void I8008::_OUT29(){

}
void I8008::_OUT30(){

}
void I8008::_OUT31(){

}

// add & add carry
void I8008::_ADA(){

}
void I8008::_ADB(){

}
void I8008::_ADC(){

}
void I8008::_ADD(){

}
void I8008::_ADE(){

}
void I8008::_ADH(){

}
void I8008::_ADL(){

}
void I8008::_ADM(){

}

void I8008::_ACA(){

}
void I8008::_ACB(){

}
void I8008::_ACC(){

}
void I8008::_ACD(){

}
void I8008::_ACE(){

}
void I8008::_ACH(){

}
void I8008::_ACL(){

}
void I8008::_ACM(){

}

// subtract & subtract carry
void I8008::_SUA(){

}
void I8008::_SUB(){

}
void I8008::_SUC(){

}
void I8008::_SUD(){

}
void I8008::_SUE(){

}
void I8008::_SUH(){

}
void I8008::_SUL(){

}
void I8008::_SUM(){

}

void I8008::_SBA(){

}
void I8008::_SBB(){

}
void I8008::_SBC(){

}
void I8008::_SBD(){

}
void I8008::_SBE(){

}
void I8008::_SBH(){

}
void I8008::_SBL(){

}
void I8008::_SBM(){

}

void I8008::_NDA(){

}
void I8008::_NDB(){

}
void I8008::_NDC(){

}
void I8008::_NDD(){

}
void I8008::_NDE(){

}
void I8008::_NDH(){

}
void I8008::_NDL(){

}
void I8008::_NDM(){

}

void I8008::_XRA(){

}
void I8008::_XRB(){

}
void I8008::_XRC(){

}
void I8008::_XRD(){

}
void I8008::_XRE(){

}
void I8008::_XRH(){

}
void I8008::_XRL(){

}
void I8008::_XRM(){

}

void I8008::_ORA(){

}
void I8008::_ORB(){

}
void I8008::_ORC(){

}
void I8008::_ORD(){

}
void I8008::_ORE(){

}
void I8008::_ORH(){

}
void I8008::_ORL(){

}
void I8008::_ORM(){

}
void I8008::_CPA(){

}
void I8008::_CPB(){

}
void I8008::_CPC(){

}
void I8008::_CPD(){

}
void I8008::_CPE(){

}
void I8008::_CPH(){

}
void I8008::_CPL(){

}
void I8008::_CPM(){

}

// loads
void I8008::_LAB(){

}
void I8008::_LAC(){

}
void I8008::_LAD(){

}
void I8008::_LAE(){

}
void I8008::_LAH(){

}
void I8008::_LAL(){

}
void I8008::_LAM(){

}

void I8008::_LBA(){

}
void I8008::_LBC(){

}
void I8008::_LBD(){

}
void I8008::_LBE(){

}
void I8008::_LBH(){

}
void I8008::_LBL(){

}
void I8008::_LBM(){

}

void I8008::_LCA(){

}
void I8008::_LCB(){

}
void I8008::_LCD(){

}
void I8008::_LCE(){

}
void I8008::_LCH(){

}
void I8008::_LCL(){

}
void I8008::_LCM(){

}

void I8008::_LDA(){

}
void I8008::_LDB(){

}
void I8008::_LDC(){

}
void I8008::_LDE(){

}
void I8008::_LDH(){

}
void I8008::_LDL(){

}
void I8008::_LDM(){

}

void I8008::_LEA(){

}
void I8008::_LEB(){

}
void I8008::_LEC(){

}
void I8008::_LED(){

}
void I8008::_LEH(){

}
void I8008::_LEL(){

}
void I8008::_LEM(){

}

void I8008::_LHA(){

}
void I8008::_LHB(){

}
void I8008::_LHC(){

}
void I8008::_LHD(){

}
void I8008::_LHE(){

}
void I8008::_LHL(){

}
void I8008::_LHM(){

}

void I8008::_LLA(){

}
void I8008::_LLB(){

}
void I8008::_LLC(){

}
void I8008::_LLD(){

}
void I8008::_LLE(){

}
void I8008::_LLH(){

}
void I8008::_LLM(){

}

void I8008::_LMA(){

}
void I8008::_LMB(){

}
void I8008::_LMC(){

}
void I8008::_LMD(){

}
void I8008::_LME(){

}
void I8008::_LMH(){

}
void I8008::_LML(){

}