#ifndef RECHERCHEMoebooru_H
#define RECHERCHEMoebooru_H

#include "constantes.h"

int setTagsMoebooru(std::string recherche, std::string page, int image_count, std::string cachePath, std::string searchIndex);
int rechercheTagsMoebooru(std::string recherche, std::string cachePath, std::string searchIndex);

#endif // RECHERCHEMoebooru_H
