#include "../header/dialogo_fichero_windows.h"
/*
#include <windows.h>

bool lee_nombre_fichero(std::string& fichero_tsp)
{
  OPENFILENAME ofn ;
  char szFile[200] ;
  ZeroMemory( &ofn, sizeof( ofn));
  ofn.lStructSize = sizeof ( ofn );
  ofn.hwndOwner = NULL  ;
  ofn.lpstrFile = szFile ;
  ofn.lpstrFile[0] = '\0';
  ofn.nMaxFile = sizeof( szFile );
  ofn.lpstrFilter = "TSP_files\0*.tsp\0";
  ofn.nFilterIndex =1;
  ofn.lpstrFileTitle = NULL ;
  ofn.nMaxFileTitle = 0 ;
  ofn.lpstrInitialDir="TSP_files";
  ofn.Flags = OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
  if (GetOpenFileName(&ofn))  // displays open file dialog box
  {
    fichero_tsp = ofn.lpstrFile;
    fichero_tsp.c_str();
    return true;
  }
  return false;
}
*/
