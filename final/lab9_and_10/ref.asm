CSEG AT 0003H
DS      3
CSEG AT 002BH
DS      3
BUFPTR			EQU			0040H
public			BUFPTR
BYTESLEFT			EQU			003EH
public			BYTESLEFT
DACACTIVE			EQU			0022H.2
public			DACACTIVE
DACBUSY			EQU			496DH
public			DACBUSY
DACINIT			EQU			4929H
public			DACINIT
_DACPLAY			EQU			4976H
public			_DACPLAY
KBCHECK			EQU			45DCH
public			KBCHECK
KBINIT			EQU			44BEH
public			KBINIT
KEYTAB			EQU			41BFH
public			KEYTAB
KEYTAB2			EQU			4293H
public			KEYTAB2
MAXKEY			EQU			0076H
public			MAXKEY
MINKEY			EQU			000DH
public			MINKEY
dacout			EQU			475DH
public			dacout
ADC0CN			EQU			00E8H
public			ADC0CN
SFRPAGE			EQU			0084H
public			SFRPAGE
IE			EQU			00A8H
public			IE
dac2init			EQU			4BE2H
public			dac2init
PCA0CN			EQU			00D8H
public			PCA0CN
IP			EQU			00B8H
public			IP
_dacstereo			EQU			4BBBH
public			_dacstereo
SMB0CN			EQU			00C0H
public			SMB0CN
_dacvolume			EQU			4869H
public			_dacvolume
CPT0CN			EQU			0088H
public			CPT0CN
SPI0CN			EQU			00F8H
public			SPI0CN
DACn			EQU			00D2H
public			DACn
_dacrate			EQU			4A76H
public			_dacrate
TMR2CN			EQU			00C8H
public			TMR2CN
DACnCN			EQU			00D4H
public			DACnCN
TF2			EQU			00C8H.7
public			TF2
isStereo			EQU			0022H.3
public			isStereo
_dacbalance			EQU			48CAH
public			_dacbalance
RCAP2			EQU			00CAH
public			RCAP2
SCON0			EQU			0098H
public			SCON0
volumeL			EQU			0049H
public			volumeL
volumeR			EQU			004AH
public			volumeR
PSW			EQU			00D0H
public			PSW
_delay_ms			EQU			4A0BH
public			_delay_ms
_delay_us			EQU			49D3H
public			_delay_us
P4MDOUT			EQU			009CH
public			P4MDOUT
__lcddata			EQU			4BC5H
public			__lcddata
P6MDOUT			EQU			009EH
public			P6MDOUT
P7MDOUT			EQU			009FH
public			P7MDOUT
EMI0CF			EQU			00A3H
public			EMI0CF
lcdrs			EQU			002BH
public			lcdrs
EMI0CN			EQU			00A2H
public			EMI0CN
lcdrw			EQU			002CH
public			lcdrw
_busy			EQU			4BEAH
public			_busy
_lcdwritec			EQU			4B03H
public			_lcdwritec
__mpuwdata			EQU			4C05H
public			__mpuwdata
__lcdcmd			EQU			4BCFH
public			__lcdcmd
_lcdcursor			EQU			4BD9H
public			_lcdcursor
_lcdwritex			EQU			4B20H
public			_lcdwritex
lcdclear			EQU			4C00H
public			lcdclear
__mpuwcmd			EQU			4C0AH
public			__mpuwcmd
_mpurdata			EQU			4C0FH
public			_mpurdata
_lcdwrite			EQU			4AA3H
public			_lcdwrite
lcdrdata			EQU			002DH
public			lcdrdata
lcdwdata			EQU			002EH
public			lcdwdata
lcdbase			EQU			002FH
public			lcdbase
_mpurcmd			EQU			4C14H
public			_mpurcmd
lcdrcmd			EQU			0030H
public			lcdrcmd
lcdwcmd			EQU			0031H
public			lcdwcmd
_lcdpos			EQU			4B57H
public			_lcdpos
lcdinit			EQU			4987H
public			lcdinit
SPI0CKR			EQU			009DH
public			SPI0CKR
P0			EQU			0080H
public			P0
SPIEN			EQU			00F8H.0
public			SPIEN
P2			EQU			00A0H
public			P2
spiinit			EQU			4AE5H
public			spiinit
P0MDOUT			EQU			00A4H
public			P0MDOUT
P2MDOUT			EQU			00A6H
public			P2MDOUT
spi_rcv_byte			EQU			4BA5H
public			spi_rcv_byte
CS			EQU			00A0H.0
public			CS
XBR0			EQU			00E1H
public			XBR0
XBR1			EQU			00E2H
public			XBR1
SPIF			EQU			00F8H.7
public			SPIF
NSSMD0			EQU			00F8H.2
public			NSSMD0
NSSMD1			EQU			00F8H.3
public			NSSMD1
_spi_rcv_buffer			EQU			4A42H
public			_spi_rcv_buffer
_spi_set_divisor			EQU			4B7AH
public			_spi_set_divisor
spi_cs_deassert			EQU			4C1CH
public			spi_cs_deassert
_spi_send_byte			EQU			4BF2H
public			_spi_send_byte
SPI0CFG			EQU			009AH
public			SPI0CFG
spicardpresent			EQU			4BFAH
public			spicardpresent
SPI0DAT			EQU			009BH
public			SPI0DAT
spi_cs_assert			EQU			4C19H
public			spi_cs_assert
_NTOHL			EQU			4BB0H
public			_NTOHL
_NTOHS			EQU			4BB7H
public			_NTOHS
songSector			EQU			0200H
public			songSector
readdir			EQU			4367H
public			readdir
numSongs			EQU			0280H
public			numSongs
_microSDread			EQU			47F5H
public			_microSDread
?_MICROSDREAD?BYTE EQU 0023H
public ?_MICROSDREAD?BYTE
microSDinit			EQU			4AC6H
public			microSDinit
?C?CLDPTR			EQU			4000H
public			?C?CLDPTR
?C?LMUL			EQU			4019H
public			?C?LMUL
?C?ULDIV			EQU			40A4H
public			?C?ULDIV
?C?LSHL			EQU			4136H
public			?C?LSHL
?C?LLDXDATA			EQU			4149H
public			?C?LLDXDATA
?C?LSTXDATA			EQU			4155H
public			?C?LSTXDATA
?C?LSTKXDATA			EQU			4161H
public			?C?LSTKXDATA
?C?ICASE			EQU			4192H
public			?C?ICASE
end