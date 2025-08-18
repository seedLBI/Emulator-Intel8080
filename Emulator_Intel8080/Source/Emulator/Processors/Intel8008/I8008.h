#ifndef I8008_H
#define I8008_H

#include "Emulator/Processors/Processor.h"

class I8008 : public Processor
{
public:
	I8008();
	~I8008();

	Momento* SaveState() override;
	void     RestoreState(Momento* momento) override;

private:

	// -----------Processort-Data-------------

	uint8_t A = 0, // Registers
			B = 0,
			C = 0,
			D = 0,
			E = 0,
			H = 0,
			L = 0;

	uint16_t PC;	// Program counter
	uint16_t SP[8]  // 8-level stack
		= {0,0,0,0,0,0,0,0}; 

	bool Sign = false,
		 Zero = false,
		 Parity = false,
		 Carry = false;

	void _NOP();
	void _HLT();

	//rotate
	void _RLC(); void _RAL(); void _RRC(); void _RAR();

	//returns
	void _RET();
	void _RFC(); void _RFS(); void _RFZ(); void _RFP();
	void _RTC(); void _RTS(); void _RTZ(); void _RTP();
	
	//rst
	void _RST0(); void _RST1(); void _RST2(); void _RST3(); void _RST4(); void _RST5(); void _RST6(); void _RST7();

	//increment & decrement
	void _INC(); void _INB(); void _INE(); void _IND(); void _INL(); void _INH();
	void _DCC(); void _DCB(); void _DCE(); void _DCD(); void _DCL(); void _DCH();

	void _ADI(); void _ACI(); void _SUI(); void _SBI(); void _NDI(); void _XRI(); void _ORI(); void _CPI();
	void _LAI(); void _LBI(); void _LCI(); void _LDI(); void _LEI(); void _LHI(); void _LLI(); void _LMI();

	//jumps
	void _JMP();
	void _JFC(); void _JFZ(); void _JFS(); void _JFP();
	void _JTC(); void _JTZ(); void _JTS(); void _JTP();
	
	//calls
	void _CAL();
	void _CFC(); void _CFZ(); void _CFS(); void _CFP();
	void _CTC(); void _CTZ(); void _CTS(); void _CTP();
	
	// inputs
	void _INP0(); void _INP1(); void _INP2(); void _INP3(); void _INP4(); void _INP5(); void _INP6(); void _INP7();
	
	// outputs
	void _OUT0();  void _OUT1();  void _OUT2();  void _OUT3();  void _OUT4();  void _OUT5();  void _OUT6();  void _OUT7();
	void _OUT8();  void _OUT9();  void _OUT10(); void _OUT11(); void _OUT12(); void _OUT13(); void _OUT14(); void _OUT15();
	void _OUT16(); void _OUT17(); void _OUT18(); void _OUT19(); void _OUT20(); void _OUT21(); void _OUT22(); void _OUT23();
	void _OUT24(); void _OUT25(); void _OUT26(); void _OUT27(); void _OUT28(); void _OUT29(); void _OUT30(); void _OUT31();

	// add & add carry
	void _ADA(); void _ADB(); void _ADC(); void _ADD(); void _ADE(); void _ADH(); void _ADL(); void _ADM();
	void _ACA(); void _ACB(); void _ACC(); void _ACD(); void _ACE(); void _ACH(); void _ACL(); void _ACM();

	// subtract & subtract carry
	void _SUA(); void _SUB(); void _SUC(); void _SUD(); void _SUE(); void _SUH(); void _SUL(); void _SUM();
	void _SBA(); void _SBB(); void _SBC(); void _SBD(); void _SBE(); void _SBH(); void _SBL(); void _SBM();

	void _NDA(); void _NDB(); void _NDC(); void _NDD(); void _NDE(); void _NDH(); void _NDL(); void _NDM();
	void _XRA(); void _XRB(); void _XRC(); void _XRD(); void _XRE(); void _XRH(); void _XRL(); void _XRM();

	void _ORA(); void _ORB(); void _ORC(); void _ORD(); void _ORE(); void _ORH(); void _ORL(); void _ORM();
	void _CPA(); void _CPB(); void _CPC(); void _CPD(); void _CPE(); void _CPH(); void _CPL(); void _CPM();

	// loads
				 void _LAB(); void _LAC(); void _LAD(); void _LAE(); void _LAH(); void _LAL(); void _LAM();
	void _LBA();			  void _LBC(); void _LBD(); void _LBE(); void _LBH(); void _LBL(); void _LBM();
	void _LCA(); void _LCB();			   void _LCD(); void _LCE(); void _LCH(); void _LCL(); void _LCM();
	void _LDA(); void _LDB(); void _LDC();			    void _LDE(); void _LDH(); void _LDL(); void _LDM();
	void _LEA(); void _LEB(); void _LEC(); void _LED();				 void _LEH(); void _LEL(); void _LEM();
	void _LHA(); void _LHB(); void _LHC(); void _LHD(); void _LHE();			  void _LHL(); void _LHM();
	void _LLA(); void _LLB(); void _LLC(); void _LLD(); void _LLE(); void _LLH();			   void _LLM();
	void _LMA(); void _LMB(); void _LMC(); void _LMD(); void _LME(); void _LMH(); void _LML();

};




#endif // !I8008
