/**********************************************************************
 Created on : 06/02/2025
 Purpose    : Print the hisgram statitics in text
 Author     : Indranil Das, Research Associate, Imperial
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/

int GetHistoStat(const char *infile="output.root"){
  
  TFile *fin = TFile::Open(infile);
  if(!fin) return false;
  
  TIter nextkey(fin->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)nextkey()) ) {
	
    TObject *obj = key->ReadObj();
    
    if ( obj->IsA()->InheritsFrom( "TH1" ) ) {
      TH1 *h1 = (TH1*)obj;
      printf("%40s, \t %02d\n",h1->GetName(),int(h1->GetEntries()));
    }//isHisto
  }//key loop
  return true;
}
