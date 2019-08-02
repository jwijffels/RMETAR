#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>
#include <R_ext/Arith.h>
#include "metar_structs.h" 

int DcdMETAR( char *, Decoded_METAR * );
void sprint_metar( char *string, Decoded_METAR *Mptr );

SEXP extract_runway_VisRange(Decoded_METAR *Mptr, int element){
  // Declare
  SEXP result = PROTECT(NEW_LIST(7));
  SEXP runway_designator = PROTECT(NEW_CHARACTER(1));
  SEXP vrbl_visRange = PROTECT(NEW_INTEGER(1));
  SEXP below_min_RVR = PROTECT(NEW_INTEGER(1));
  SEXP above_max_RVR = PROTECT(NEW_INTEGER(1));
  SEXP visRange = PROTECT(NEW_INTEGER(1));
  SEXP Max_visRange = PROTECT(NEW_INTEGER(1));
  SEXP Min_visRange = PROTECT(NEW_INTEGER(1));
  
  // Set the list names
  SEXP listnames = PROTECT(NEW_CHARACTER(7));
  const char *names[7] = { "runway_designator", 
    "vrbl_visRange", "below_min_RVR", "above_max_RVR", 
    "visRange", "Max_visRange", "Min_visRange" };  
  for (int i = 0; i < 7; i++) SET_STRING_ELT(listnames, i, mkChar(names[i]));
  SET_NAMES(result, listnames);
  
  // Assign values
  if(Mptr->RRVR[element].runway_designator[0] != '\0') SET_STRING_ELT(runway_designator, 0, mkChar(Mptr->RRVR[element].runway_designator)); else SET_STRING_ELT(runway_designator, 0, NA_STRING);
  if(Mptr->RRVR[element].vrbl_visRange != MAXINT) vrbl_visRange = ScalarInteger(Mptr->RRVR[element].vrbl_visRange); else vrbl_visRange = ScalarInteger(NA_INTEGER);
  if(Mptr->RRVR[element].below_min_RVR != MAXINT) below_min_RVR = ScalarInteger(Mptr->RRVR[element].below_min_RVR); else below_min_RVR = ScalarInteger(NA_INTEGER);
  if(Mptr->RRVR[element].above_max_RVR != MAXINT) above_max_RVR = ScalarInteger(Mptr->RRVR[element].above_max_RVR); else above_max_RVR = ScalarInteger(NA_INTEGER);
  if(Mptr->RRVR[element].visRange != MAXINT) visRange = ScalarInteger(Mptr->RRVR[element].visRange); else visRange = ScalarInteger(NA_INTEGER);
  if(Mptr->RRVR[element].Max_visRange != MAXINT) Max_visRange = ScalarInteger(Mptr->RRVR[element].Max_visRange); else Max_visRange = ScalarInteger(NA_INTEGER);
  if(Mptr->RRVR[element].Min_visRange != MAXINT) Min_visRange = ScalarInteger(Mptr->RRVR[element].Min_visRange); else Min_visRange = ScalarInteger(NA_INTEGER);

  // Add them to the list
  SET_ELEMENT(result, 0, runway_designator);
  SET_ELEMENT(result, 1, vrbl_visRange);
  SET_ELEMENT(result, 2, below_min_RVR);
  SET_ELEMENT(result, 3, above_max_RVR);
  SET_ELEMENT(result, 4, visRange);
  SET_ELEMENT(result, 5, Max_visRange);
  SET_ELEMENT(result, 6, Min_visRange);
  UNPROTECT(9);
  return(result);
}

SEXP extract_dispatch_VisRange(Decoded_METAR *Mptr){
  // Declare
  SEXP result = PROTECT(NEW_LIST(6));
  SEXP vrbl_visRange = PROTECT(NEW_INTEGER(1));
  SEXP below_min_DVR = PROTECT(NEW_INTEGER(1));
  SEXP above_max_DVR = PROTECT(NEW_INTEGER(1));
  SEXP visRange = PROTECT(NEW_INTEGER(1));
  SEXP Max_visRange = PROTECT(NEW_INTEGER(1));
  SEXP Min_visRange = PROTECT(NEW_INTEGER(1));
  
  // Set the list names
  SEXP listnames = PROTECT(NEW_CHARACTER(6));
  const char *names[6] = { "vrbl_visRange", "below_min_DVR", "above_max_DVR", "visRange", "Max_visRange", "Min_visRange" };  
  for (int i = 0; i < 6; i++) SET_STRING_ELT(listnames, i, mkChar(names[i]));
  SET_NAMES(result, listnames);
  
  // Assign values
  if(Mptr->DVR.vrbl_visRange != MAXINT) vrbl_visRange = ScalarInteger(Mptr->DVR.vrbl_visRange); else vrbl_visRange = ScalarInteger(NA_INTEGER);
  if(Mptr->DVR.below_min_DVR != MAXINT) below_min_DVR = ScalarInteger(Mptr->DVR.below_min_DVR); else below_min_DVR = ScalarInteger(NA_INTEGER);
  if(Mptr->DVR.above_max_DVR != MAXINT) above_max_DVR = ScalarInteger(Mptr->DVR.above_max_DVR); else above_max_DVR = ScalarInteger(NA_INTEGER);
  if(Mptr->DVR.visRange != MAXINT) visRange = ScalarInteger(Mptr->DVR.visRange); else visRange = ScalarInteger(NA_INTEGER);
  if(Mptr->DVR.Max_visRange != MAXINT) Max_visRange = ScalarInteger(Mptr->DVR.Max_visRange); else Max_visRange = ScalarInteger(NA_INTEGER);
  if(Mptr->DVR.Min_visRange != MAXINT) Min_visRange = ScalarInteger(Mptr->DVR.Min_visRange); else Min_visRange = ScalarInteger(NA_INTEGER);

  // Add them to the list
  SET_ELEMENT(result, 0, vrbl_visRange);
  SET_ELEMENT(result, 1, below_min_DVR);
  SET_ELEMENT(result, 2, above_max_DVR);
  SET_ELEMENT(result, 3, visRange);
  SET_ELEMENT(result, 4, Max_visRange);
  SET_ELEMENT(result, 5, Min_visRange);
  UNPROTECT(8);
  return(result);
}

SEXP extract_recent_wx(Decoded_METAR *Mptr, int element){
  // Declare
  SEXP result = PROTECT(NEW_LIST(5));
  SEXP Recent_weather = PROTECT(NEW_CHARACTER(1));
  SEXP Bhh = PROTECT(NEW_INTEGER(1));
  SEXP Bmm = PROTECT(NEW_INTEGER(1));
  SEXP Ehh = PROTECT(NEW_INTEGER(1));
  SEXP Emm = PROTECT(NEW_INTEGER(1));
  
  // Set the list names
  SEXP listnames = PROTECT(NEW_CHARACTER(5));
  const char *names[5] = { "Recent_weather", "Bhh", "Bmm", "Ehh", "Emm" };  
  for (int i = 0; i < 5; i++) SET_STRING_ELT(listnames, i, mkChar(names[i]));
  SET_NAMES(result, listnames);
  
  // Assign values
  if(Mptr->ReWx[element].Recent_weather[0] != '\0') SET_STRING_ELT(Recent_weather, 0, mkChar(Mptr->ReWx[element].Recent_weather)); else SET_STRING_ELT(Recent_weather, 0, NA_STRING);
  if(Mptr->ReWx[element].Bhh != MAXINT) Bhh = ScalarInteger(Mptr->ReWx[element].Bhh); else Bhh = ScalarInteger(NA_INTEGER);
  if(Mptr->ReWx[element].Bmm != MAXINT) Bmm = ScalarInteger(Mptr->ReWx[element].Bmm); else Bmm = ScalarInteger(NA_INTEGER);
  if(Mptr->ReWx[element].Ehh != MAXINT) Ehh = ScalarInteger(Mptr->ReWx[element].Ehh); else Ehh = ScalarInteger(NA_INTEGER);
  if(Mptr->ReWx[element].Emm != MAXINT) Emm = ScalarInteger(Mptr->ReWx[element].Emm); else Emm = ScalarInteger(NA_INTEGER);

  // Add them to the list
  SET_ELEMENT(result, 0, Recent_weather);
  SET_ELEMENT(result, 1, Bhh);
  SET_ELEMENT(result, 2, Bmm);
  SET_ELEMENT(result, 3, Ehh);
  SET_ELEMENT(result, 4, Emm);
  UNPROTECT(7);
  return(result);
}

SEXP extract_windstruct(Decoded_METAR *Mptr){
  // Declare
  SEXP result = PROTECT(NEW_LIST(5));
  SEXP windUnits = PROTECT(NEW_CHARACTER(1));
  SEXP windVRB = PROTECT(NEW_INTEGER(1));
  SEXP windDir = PROTECT(NEW_INTEGER(1));
  SEXP windSpeed = PROTECT(NEW_INTEGER(1));
  SEXP windGust = PROTECT(NEW_INTEGER(1));
  
  // Set the list names
  SEXP listnames = PROTECT(NEW_CHARACTER(5));
  const char *names[5] = { "windUnits", "windVRB", "windDir", "windSpeed", "windGust" };  
  for (int i = 0; i < 5; i++) SET_STRING_ELT(listnames, i, mkChar(names[i]));
  SET_NAMES(result, listnames);
  
  // Assign values
  if(Mptr->winData.windUnits[0] != '\0') SET_STRING_ELT(windUnits, 0, mkChar(Mptr->winData.windUnits)); else SET_STRING_ELT(windUnits, 0, NA_STRING);
  if(Mptr->winData.windVRB != MAXINT) windVRB = ScalarInteger(Mptr->winData.windVRB); else windVRB = ScalarInteger(NA_INTEGER);
  if(Mptr->winData.windDir != MAXINT) windDir = ScalarInteger(Mptr->winData.windDir); else windDir = ScalarInteger(NA_INTEGER);
  if(Mptr->winData.windSpeed != MAXINT) windSpeed = ScalarInteger(Mptr->winData.windSpeed); else windSpeed = ScalarInteger(NA_INTEGER);
  if(Mptr->winData.windGust != MAXINT) windGust = ScalarInteger(Mptr->winData.windGust); else windGust = ScalarInteger(NA_INTEGER);

  // Add them to the list
  SET_ELEMENT(result, 0, windUnits);
  SET_ELEMENT(result, 1, windVRB);
  SET_ELEMENT(result, 2, windDir);
  SET_ELEMENT(result, 3, windSpeed);
  SET_ELEMENT(result, 4, windGust);
  UNPROTECT(7);
  return(result);
}


SEXP extract_cloud_Conditions(Decoded_METAR *Mptr, int element){
  // Declare
  SEXP result = PROTECT(NEW_LIST(4));
  SEXP cloud_type = PROTECT(NEW_CHARACTER(1));
  SEXP cloud_hgt_char = PROTECT(NEW_CHARACTER(1));
  SEXP other_cld_phenom = PROTECT(NEW_CHARACTER(1));
  SEXP cloud_hgt_meters = PROTECT(NEW_INTEGER(1));
  
  // Set the list names
  SEXP listnames = PROTECT(NEW_CHARACTER(4));
  const char *names[4] = { "cloud_type", "cloud_hgt_char", "other_cld_phenom", "cloud_hgt_meters" };  
  for (int i = 0; i < 4; i++) SET_STRING_ELT(listnames, i, mkChar(names[i]));
  SET_NAMES(result, listnames);
  
  // Assign values
  if(Mptr->cldTypHgt[element].cloud_type[0] != '\0') SET_STRING_ELT(cloud_type, 0, mkChar(Mptr->cldTypHgt[element].cloud_type)); else SET_STRING_ELT(cloud_type, 0, NA_STRING);
  if(Mptr->cldTypHgt[element].cloud_hgt_char[0] != '\0') SET_STRING_ELT(cloud_hgt_char, 0, mkChar(Mptr->cldTypHgt[element].cloud_hgt_char)); else SET_STRING_ELT(cloud_hgt_char, 0, NA_STRING);
  if(Mptr->cldTypHgt[element].other_cld_phenom[0] != '\0') SET_STRING_ELT(other_cld_phenom, 0, mkChar(Mptr->cldTypHgt[element].other_cld_phenom)); else SET_STRING_ELT(other_cld_phenom, 0, NA_STRING);
  if(Mptr->cldTypHgt[element].cloud_hgt_meters != MAXINT) cloud_hgt_meters = ScalarInteger( Mptr->cldTypHgt[element].cloud_hgt_meters); else cloud_hgt_meters = ScalarInteger(NA_INTEGER);

  // Add them to the list
  SET_ELEMENT(result, 0, cloud_type);
  SET_ELEMENT(result, 1, cloud_hgt_char);
  SET_ELEMENT(result, 2, other_cld_phenom);
  SET_ELEMENT(result, 3, cloud_hgt_meters);
  UNPROTECT(6);
  return(result);
}

SEXP decodeMETAR(SEXP metarcode, SEXP printdecodedmetar) {
  PROTECT(metarcode = AS_CHARACTER(metarcode));
  PROTECT(printdecodedmetar = AS_INTEGER(printdecodedmetar));
  
  int i;
  char printout[5000];
  // Create the output list
  SEXP result = PROTECT(NEW_LIST(10));
  SEXP result_characters = PROTECT(NEW_LIST(5));
  SEXP result_characters_single = PROTECT(NEW_CHARACTER(30));
  SEXP result_characters_WxObstruct = PROTECT(NEW_CHARACTER(10));
  SEXP result_characters_PartialObscurationAmt = PROTECT(NEW_CHARACTER(2));
  SEXP result_characters_PartialObscurationPhenom = PROTECT(NEW_CHARACTER(2));
  SEXP result_characters_SfcObscuration = PROTECT(NEW_CHARACTER(6));
  SEXP result_mdsp_bool = PROTECT(NEW_INTEGER(42));
  SEXP result_integers = PROTECT(NEW_INTEGER(37));
  SEXP result_numerics = PROTECT(NEW_NUMERIC(23));  
  SEXP result_Runway_VisRange = PROTECT(NEW_LIST(12));
  SEXP result_Recent_Wx = PROTECT(NEW_LIST(3));
  SEXP result_Cloud_Conditions = PROTECT(NEW_LIST(6));
  SEXP result_printout = PROTECT(NEW_CHARACTER(1));

  // Copy the input code 
  char inputstring[strlen(CHAR(STRING_ELT(metarcode, 0)))];  
  strcpy(inputstring, CHAR(STRING_ELT(metarcode, 0)));  
  
  // Make the SEXP point to the C ones
  int *dcdmetar_mdsp_bool;     
  int *dcdmetar_integers;  
  double *dcdmetar_numerics;
  dcdmetar_mdsp_bool = INTEGER_POINTER(result_mdsp_bool);
  dcdmetar_integers = INTEGER_POINTER(result_integers);
  dcdmetar_numerics = NUMERIC_POINTER(result_numerics);
  
  // Decode the metar code
  Decoded_METAR Metar;
  Decoded_METAR *Mptr = &Metar;
  int ErReturn;
  ErReturn = DcdMETAR(inputstring, Mptr);
  sprint_metar(printout, Mptr);
  SET_STRING_ELT(result_printout, 0, mkChar(printout));
  
  // char part of the decoded_METAR struct
  if(Mptr->synoptic_cloud_type[0] != '\0') SET_STRING_ELT(result_characters_single, 0, mkChar(Mptr->synoptic_cloud_type)); else SET_STRING_ELT(result_characters_single, 0, NA_STRING);
  if(Mptr->snow_depth_group[0] != '\0') SET_STRING_ELT(result_characters_single, 1, mkChar(Mptr->snow_depth_group)); else SET_STRING_ELT(result_characters_single, 1, NA_STRING);
  if(Mptr->codeName[0] != '\0') SET_STRING_ELT(result_characters_single, 2, mkChar(Mptr->codeName)); else SET_STRING_ELT(result_characters_single, 2, NA_STRING);
  if(Mptr->stnid[0] != '\0') SET_STRING_ELT(result_characters_single, 3, mkChar(Mptr->stnid)); else SET_STRING_ELT(result_characters_single, 3, NA_STRING);
  if(Mptr->horiz_vsby[0] != '\0') SET_STRING_ELT(result_characters_single, 4, mkChar(Mptr->horiz_vsby)); else SET_STRING_ELT(result_characters_single, 4, NA_STRING);
  if(Mptr->dir_min_horiz_vsby[0] != '\0') SET_STRING_ELT(result_characters_single, 5, mkChar(Mptr->dir_min_horiz_vsby)); else SET_STRING_ELT(result_characters_single, 5, NA_STRING);
  if(Mptr->vsby_Dir[0] != '\0') SET_STRING_ELT(result_characters_single, 6, mkChar(Mptr->vsby_Dir)); else SET_STRING_ELT(result_characters_single, 6, NA_STRING);
  if(Mptr->autoIndicator[0] != '\0') SET_STRING_ELT(result_characters_single, 7, mkChar(Mptr->autoIndicator)); else SET_STRING_ELT(result_characters_single, 7, NA_STRING);
  if(Mptr->VSBY_2ndSite_LOC[0] != '\0') SET_STRING_ELT(result_characters_single, 8, mkChar(Mptr->VSBY_2ndSite_LOC)); else SET_STRING_ELT(result_characters_single, 8, NA_STRING);
  if(Mptr->SKY_2ndSite_LOC[0] != '\0') SET_STRING_ELT(result_characters_single, 9, mkChar(Mptr->SKY_2ndSite_LOC)); else SET_STRING_ELT(result_characters_single, 9, NA_STRING);
  if(Mptr->SKY_2ndSite[0] != '\0') SET_STRING_ELT(result_characters_single, 10, mkChar(Mptr->SKY_2ndSite)); else SET_STRING_ELT(result_characters_single, 10, NA_STRING);
  if(Mptr->SectorVsby_Dir[0] != '\0') SET_STRING_ELT(result_characters_single, 11, mkChar(Mptr->SectorVsby_Dir)); else SET_STRING_ELT(result_characters_single, 11, NA_STRING);
  if(Mptr->ObscurAloft[0] != '\0') SET_STRING_ELT(result_characters_single, 12, mkChar(Mptr->ObscurAloft)); else SET_STRING_ELT(result_characters_single, 12, NA_STRING);
  if(Mptr->ObscurAloftSkyCond[0] != '\0') SET_STRING_ELT(result_characters_single, 13, mkChar(Mptr->ObscurAloftSkyCond)); else SET_STRING_ELT(result_characters_single, 13, NA_STRING);
  if(Mptr->VrbSkyBelow[0] != '\0') SET_STRING_ELT(result_characters_single, 14, mkChar(Mptr->VrbSkyBelow)); else SET_STRING_ELT(result_characters_single, 14, NA_STRING);
  if(Mptr->VrbSkyAbove[0] != '\0') SET_STRING_ELT(result_characters_single, 15, mkChar(Mptr->VrbSkyAbove)); else SET_STRING_ELT(result_characters_single, 15, NA_STRING);
  if(Mptr->LTG_DIR[0] != '\0') SET_STRING_ELT(result_characters_single, 16, mkChar(Mptr->LTG_DIR)); else SET_STRING_ELT(result_characters_single, 16, NA_STRING);
  char CloudLowMediumHigh[3];
  CloudLowMediumHigh[0] = Mptr->CloudLow;
  CloudLowMediumHigh[1] = Mptr->CloudMedium;
  CloudLowMediumHigh[2] = Mptr->CloudHigh;
  if(CloudLowMediumHigh[0] != '\0' | CloudLowMediumHigh[1] != '\0' | CloudLowMediumHigh[2] != '\0') SET_STRING_ELT(result_characters_single, 17, mkChar(CloudLowMediumHigh)); else SET_STRING_ELT(result_characters_single, 17, NA_STRING);
  if(Mptr->CIG_2ndSite_LOC[0] != '\0') SET_STRING_ELT(result_characters_single, 18, mkChar(Mptr->CIG_2ndSite_LOC)); else SET_STRING_ELT(result_characters_single, 18, NA_STRING);
  if(Mptr->VIRGA_DIR[0] != '\0') SET_STRING_ELT(result_characters_single, 19, mkChar(Mptr->VIRGA_DIR)); else SET_STRING_ELT(result_characters_single, 19, NA_STRING);
  if(Mptr->TornadicType[0] != '\0') SET_STRING_ELT(result_characters_single, 20, mkChar(Mptr->TornadicType)); else SET_STRING_ELT(result_characters_single, 20, NA_STRING);
  if(Mptr->TornadicLOC[0] != '\0') SET_STRING_ELT(result_characters_single, 21, mkChar(Mptr->TornadicLOC)); else SET_STRING_ELT(result_characters_single, 21, NA_STRING);
  if(Mptr->TornadicDIR[0] != '\0') SET_STRING_ELT(result_characters_single, 22, mkChar(Mptr->TornadicDIR)); else SET_STRING_ELT(result_characters_single, 22, NA_STRING);
  if(Mptr->TornadicMovDir[0] != '\0') SET_STRING_ELT(result_characters_single, 23, mkChar(Mptr->TornadicMovDir)); else SET_STRING_ELT(result_characters_single, 23, NA_STRING);
  if(Mptr->CHINO_LOC[0] != '\0') SET_STRING_ELT(result_characters_single, 24, mkChar(Mptr->CHINO_LOC)); else SET_STRING_ELT(result_characters_single, 24, NA_STRING);
  if(Mptr->VISNO_LOC[0] != '\0') SET_STRING_ELT(result_characters_single, 25, mkChar(Mptr->VISNO_LOC)); else SET_STRING_ELT(result_characters_single, 25, NA_STRING);
  if(Mptr->charPrevailVsby[0] != '\0') SET_STRING_ELT(result_characters_single, 26, mkChar(Mptr->charPrevailVsby)); else SET_STRING_ELT(result_characters_single, 26, NA_STRING);
  if(Mptr->charVertVsby[0] != '\0') SET_STRING_ELT(result_characters_single, 27, mkChar(Mptr->charVertVsby)); else SET_STRING_ELT(result_characters_single, 27, NA_STRING);
  if(Mptr->TS_LOC[0] != '\0') SET_STRING_ELT(result_characters_single, 28, mkChar(Mptr->TS_LOC)); else SET_STRING_ELT(result_characters_single, 28, NA_STRING);
  if(Mptr->TS_MOVMNT[0] != '\0') SET_STRING_ELT(result_characters_single, 29, mkChar(Mptr->TS_MOVMNT)); else SET_STRING_ELT(result_characters_single, 29, NA_STRING);
  for(i = 0; i < 10; i++) if(Mptr->WxObstruct[i][0] != '\0') SET_STRING_ELT(result_characters_WxObstruct, i, mkChar(Mptr->WxObstruct[i])); else SET_STRING_ELT(result_characters_WxObstruct, i, NA_STRING);
  for(i = 0; i < 2; i++) if(Mptr->PartialObscurationAmt[i][0] != '\0') SET_STRING_ELT(result_characters_PartialObscurationAmt, i, mkChar(Mptr->PartialObscurationAmt[i])); else SET_STRING_ELT(result_characters_PartialObscurationAmt, i, NA_STRING);
  for(i = 0; i < 2; i++) if(Mptr->PartialObscurationPhenom[i][0] != '\0') SET_STRING_ELT(result_characters_PartialObscurationPhenom, i, mkChar(Mptr->PartialObscurationPhenom[i])); else SET_STRING_ELT(result_characters_PartialObscurationPhenom, i, NA_STRING);
  for(i = 0; i < 6; i++) if(Mptr->synoptic_cloud_type[0] != '\0') SET_STRING_ELT(result_characters_SfcObscuration, i, mkChar(Mptr->SfcObscuration[i])); else SET_STRING_ELT(result_characters_SfcObscuration, i, NA_STRING);
    
  // MDSP_BOOL part of the decoded_METAR struct
  dcdmetar_mdsp_bool[0] = Mptr->Indeterminant3_6HrPrecip;
  dcdmetar_mdsp_bool[1] = Mptr->Indeterminant_24HrPrecip;
  dcdmetar_mdsp_bool[2] = Mptr->CIGNO;
  dcdmetar_mdsp_bool[3] = Mptr->SLPNO;
  dcdmetar_mdsp_bool[4] = Mptr->ACFTMSHP;
  dcdmetar_mdsp_bool[5] = Mptr->NOSPECI;
  dcdmetar_mdsp_bool[6] = Mptr->FIRST;
  dcdmetar_mdsp_bool[7] = Mptr->LAST;
  dcdmetar_mdsp_bool[8] = Mptr->SunSensorOut;
  dcdmetar_mdsp_bool[9] = Mptr->AUTO;
  dcdmetar_mdsp_bool[10] = Mptr->COR;
  dcdmetar_mdsp_bool[11] = Mptr->NIL_rpt;
  dcdmetar_mdsp_bool[12] = Mptr->CAVOK;
  dcdmetar_mdsp_bool[13] = Mptr->RVRNO;
  dcdmetar_mdsp_bool[14] = Mptr->A_altstng;
  dcdmetar_mdsp_bool[15] = Mptr->Q_altstng;
  dcdmetar_mdsp_bool[16] = Mptr->VIRGA;
  dcdmetar_mdsp_bool[17] = Mptr->VOLCASH;
  dcdmetar_mdsp_bool[18] = Mptr->GR;
  dcdmetar_mdsp_bool[19] = Mptr->CHINO;
  dcdmetar_mdsp_bool[20] = Mptr->VISNO;
  dcdmetar_mdsp_bool[21] = Mptr->PNO;
  dcdmetar_mdsp_bool[22] = Mptr->PWINO;
  dcdmetar_mdsp_bool[23] = Mptr->FZRANO;
  dcdmetar_mdsp_bool[24] = Mptr->TSNO;
  dcdmetar_mdsp_bool[25] = Mptr->DollarSign;
  dcdmetar_mdsp_bool[26] = Mptr->PRESRR;
  dcdmetar_mdsp_bool[27] = Mptr->PRESFR;
  dcdmetar_mdsp_bool[28] = Mptr->Wshft_FROPA;
  dcdmetar_mdsp_bool[29] = Mptr->OCNL_LTG;
  dcdmetar_mdsp_bool[30] = Mptr->FRQ_LTG;
  dcdmetar_mdsp_bool[31] = Mptr->CNS_LTG;
  dcdmetar_mdsp_bool[32] = Mptr->CG_LTG;
  dcdmetar_mdsp_bool[33] = Mptr->IC_LTG;
  dcdmetar_mdsp_bool[34] = Mptr->CC_LTG;
  dcdmetar_mdsp_bool[35] = Mptr->CA_LTG;
  dcdmetar_mdsp_bool[36] = Mptr->DSNT_LTG;
  dcdmetar_mdsp_bool[37] = Mptr->AP_LTG;
  dcdmetar_mdsp_bool[38] = Mptr->VcyStn_LTG;
  dcdmetar_mdsp_bool[39] = Mptr->OVHD_LTG;
  dcdmetar_mdsp_bool[40] = Mptr->LightningVCTS;
  dcdmetar_mdsp_bool[41] = Mptr->LightningTS;
  
  // int part of the decoded_METAR struct
  dcdmetar_integers[0] = Mptr->TornadicDistance;
  dcdmetar_integers[1] = Mptr->ob_hour;
  dcdmetar_integers[2] = Mptr->ob_minute;
  dcdmetar_integers[3] = Mptr->ob_date;
  dcdmetar_integers[4] = Mptr->minWnDir;
  dcdmetar_integers[5] = Mptr->maxWnDir;
  dcdmetar_integers[6] = Mptr->VertVsby;
  dcdmetar_integers[7] = Mptr->temp;
  dcdmetar_integers[8] = Mptr->dew_pt_temp;
  dcdmetar_integers[9] = Mptr->QFE;
  dcdmetar_integers[10] = Mptr->hectoPasc_altstng;
  dcdmetar_integers[11] = Mptr->char_prestndcy;
  dcdmetar_integers[12] = Mptr->minCeiling;
  dcdmetar_integers[13] = Mptr->maxCeiling;
  dcdmetar_integers[14] = Mptr->WshfTime_hour;
  dcdmetar_integers[15] = Mptr->WshfTime_minute;
  dcdmetar_integers[16] = Mptr->min_vrbl_wind_dir;
  dcdmetar_integers[17] = Mptr->max_vrbl_wind_dir;
  dcdmetar_integers[18] = Mptr->PKWND_dir;
  dcdmetar_integers[19] = Mptr->PKWND_speed;
  dcdmetar_integers[20] = Mptr->PKWND_hour;
  dcdmetar_integers[21] = Mptr->PKWND_minute;
  dcdmetar_integers[22] = Mptr->SKY_2ndSite_Meters;
  dcdmetar_integers[23] = Mptr->Ceiling;
  dcdmetar_integers[24] = Mptr->Estimated_Ceiling;
  dcdmetar_integers[25] = Mptr->SNINCR;
  dcdmetar_integers[26] = Mptr->SNINCR_TotalDepth;
  dcdmetar_integers[27] = Mptr->SunshineDur;
  dcdmetar_integers[28] = Mptr->ObscurAloftHgt;
  dcdmetar_integers[29] = Mptr->VrbSkyLayerHgt;
  dcdmetar_integers[30] = Mptr->Num8thsSkyObscured;
  dcdmetar_integers[31] = Mptr->CIG_2ndSite_Meters;
  dcdmetar_integers[32] = Mptr->snow_depth;
  dcdmetar_integers[33] = Mptr->BTornadicHour;
  dcdmetar_integers[34] = Mptr->BTornadicMinute;
  dcdmetar_integers[35] = Mptr->ETornadicHour;
  dcdmetar_integers[36] = Mptr->ETornadicMinute;
  
  // float and real part of the decoded_METAR struct
  dcdmetar_numerics[1] = Mptr->SectorVsby;
  dcdmetar_numerics[2] = Mptr->WaterEquivSnow;
  dcdmetar_numerics[3] = Mptr->VSBY_2ndSite;
  dcdmetar_numerics[4] = Mptr->prevail_vsbySM;
  dcdmetar_numerics[5] = Mptr->prevail_vsbyM;
  dcdmetar_numerics[6] = Mptr->prevail_vsbyKM;
  dcdmetar_numerics[7] = Mptr->prestndcy;
  dcdmetar_numerics[8] = Mptr->precip_amt;
  dcdmetar_numerics[9] = Mptr->precip_24_amt;
  dcdmetar_numerics[10] = Mptr->maxtemp;
  dcdmetar_numerics[11] = Mptr->mintemp;
  dcdmetar_numerics[12] = Mptr->max24temp;
  dcdmetar_numerics[13] = Mptr->min24temp;
  dcdmetar_numerics[14] = Mptr->minVsby;
  dcdmetar_numerics[15] = Mptr->maxVsby;
  dcdmetar_numerics[16] = Mptr->hourlyPrecip;
  dcdmetar_numerics[17] = Mptr->TWR_VSBY;
  dcdmetar_numerics[18] = Mptr->SFC_VSBY;
  dcdmetar_numerics[19] = Mptr->Temp_2_tenths;
  dcdmetar_numerics[20] = Mptr->DP_Temp_2_tenths;
  dcdmetar_numerics[21] = Mptr->SLP;
  dcdmetar_numerics[22] = Mptr->GR_Size;
  dcdmetar_numerics[23] = Mptr->inches_altstng;

  // Cleaning up
  SET_STRING_ELT(result_characters_single, 9, NA_STRING); // Apparently full of crappy parsed data - also not used in prtDMETR
  SET_STRING_ELT(result_characters_single, 10, NA_STRING); // Apparently full of crappy parsed data - also not used in prtDMETR
  for (int i = 0; i < 37; i++) if(dcdmetar_integers[i] == MAXINT ) dcdmetar_integers[i] = NA_INTEGER;
  for (int i = 0; i < 23; i++) if(dcdmetar_numerics[i] == (float) MAXINT ) dcdmetar_numerics[i] = NA_REAL;
  //if(dcdmetar_numerics[23] == (double) MAXINT ) dcdmetar_numerics[23] = NA_REAL;

  // Extra, special elements in the metar struct
  SEXP result_Runway_VisRange_0 = PROTECT(extract_runway_VisRange(Mptr, 0));
  SEXP result_Runway_VisRange_1 = PROTECT(extract_runway_VisRange(Mptr, 1));
  SEXP result_Runway_VisRange_2 = PROTECT(extract_runway_VisRange(Mptr, 2));
  SEXP result_Runway_VisRange_3 = PROTECT(extract_runway_VisRange(Mptr, 3));
  SEXP result_Runway_VisRange_4 = PROTECT(extract_runway_VisRange(Mptr, 4));
  SEXP result_Runway_VisRange_5 = PROTECT(extract_runway_VisRange(Mptr, 5));
  SEXP result_Runway_VisRange_6 = PROTECT(extract_runway_VisRange(Mptr, 6));
  SEXP result_Runway_VisRange_7 = PROTECT(extract_runway_VisRange(Mptr, 7));
  SEXP result_Runway_VisRange_8 = PROTECT(extract_runway_VisRange(Mptr, 8));
  SEXP result_Runway_VisRange_9 = PROTECT(extract_runway_VisRange(Mptr, 9));
  SEXP result_Runway_VisRange_10 = PROTECT(extract_runway_VisRange(Mptr, 10));
  SEXP result_Runway_VisRange_11 = PROTECT(extract_runway_VisRange(Mptr, 11));  
  SEXP result_dispatch_VisRange = PROTECT(extract_dispatch_VisRange(Mptr));  
  SEXP result_Recent_Wx_0 = PROTECT(extract_recent_wx(Mptr, 0));
  SEXP result_Recent_Wx_1 = PROTECT(extract_recent_wx(Mptr, 1));
  SEXP result_Recent_Wx_2 = PROTECT(extract_recent_wx(Mptr, 2));
  SEXP result_windstruct = PROTECT(extract_windstruct(Mptr));  
  SEXP result_Cloud_Conditions_0 = PROTECT(extract_cloud_Conditions(Mptr, 0));
  SEXP result_Cloud_Conditions_1 = PROTECT(extract_cloud_Conditions(Mptr, 1));
  SEXP result_Cloud_Conditions_2 = PROTECT(extract_cloud_Conditions(Mptr, 2));
  SEXP result_Cloud_Conditions_3 = PROTECT(extract_cloud_Conditions(Mptr, 3));
  SEXP result_Cloud_Conditions_4 = PROTECT(extract_cloud_Conditions(Mptr, 4));
  SEXP result_Cloud_Conditions_5 = PROTECT(extract_cloud_Conditions(Mptr, 5));
  
  // Pushing it to the output list
  SET_ELEMENT(result_characters, 0, result_characters_single);
  SET_ELEMENT(result_characters, 1, result_characters_WxObstruct);
  SET_ELEMENT(result_characters, 2, result_characters_PartialObscurationAmt);
  SET_ELEMENT(result_characters, 3, result_characters_PartialObscurationPhenom);
  SET_ELEMENT(result_characters, 4, result_characters_SfcObscuration);  
  SET_ELEMENT(result, 0, result_characters);
  SET_ELEMENT(result, 1, result_mdsp_bool);  
  SET_ELEMENT(result, 2, result_integers);  
  SET_ELEMENT(result, 3, result_numerics);  

  SET_ELEMENT(result_Runway_VisRange, 0, result_Runway_VisRange_0);
  SET_ELEMENT(result_Runway_VisRange, 1, result_Runway_VisRange_1);
  SET_ELEMENT(result_Runway_VisRange, 2, result_Runway_VisRange_2);
  SET_ELEMENT(result_Runway_VisRange, 3, result_Runway_VisRange_3);
  SET_ELEMENT(result_Runway_VisRange, 4, result_Runway_VisRange_4);
  SET_ELEMENT(result_Runway_VisRange, 5, result_Runway_VisRange_5);
  SET_ELEMENT(result_Runway_VisRange, 6, result_Runway_VisRange_6);
  SET_ELEMENT(result_Runway_VisRange, 7, result_Runway_VisRange_7);
  SET_ELEMENT(result_Runway_VisRange, 8, result_Runway_VisRange_8);
  SET_ELEMENT(result_Runway_VisRange, 9, result_Runway_VisRange_9);
  SET_ELEMENT(result_Runway_VisRange, 10, result_Runway_VisRange_10);
  SET_ELEMENT(result_Runway_VisRange, 11, result_Runway_VisRange_11);
  SET_ELEMENT(result, 4, result_Runway_VisRange);
  SET_ELEMENT(result, 5, result_dispatch_VisRange);
  SET_ELEMENT(result_Recent_Wx, 0, result_Recent_Wx_0);
  SET_ELEMENT(result_Recent_Wx, 1, result_Recent_Wx_1);
  SET_ELEMENT(result_Recent_Wx, 2, result_Recent_Wx_2);  
  SET_ELEMENT(result, 6, result_Recent_Wx);
  SET_ELEMENT(result, 7, result_windstruct);    
  SET_ELEMENT(result_Cloud_Conditions, 0, result_Cloud_Conditions_0);
  SET_ELEMENT(result_Cloud_Conditions, 1, result_Cloud_Conditions_1);
  SET_ELEMENT(result_Cloud_Conditions, 2, result_Cloud_Conditions_2);
  SET_ELEMENT(result_Cloud_Conditions, 3, result_Cloud_Conditions_3);
  SET_ELEMENT(result_Cloud_Conditions, 4, result_Cloud_Conditions_4);
  SET_ELEMENT(result_Cloud_Conditions, 5, result_Cloud_Conditions_5);
  SET_ELEMENT(result, 8, result_Cloud_Conditions);
  SET_ELEMENT(result, 9, result_printout);

  UNPROTECT(39);
  return(result);
}
