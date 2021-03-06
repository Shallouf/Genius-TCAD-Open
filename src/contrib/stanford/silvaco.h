/********************************************************************************/
/*     888888    888888888   88     888  88888   888      888    88888888       */
/*   8       8   8           8 8     8     8      8        8    8               */
/*  8            8           8  8    8     8      8        8    8               */
/*  8            888888888   8   8   8     8      8        8     8888888        */
/*  8      8888  8           8    8  8     8      8        8            8       */
/*   8       8   8           8     8 8     8      8        8            8       */
/*     888888    888888888  888     88   88888     88888888     88888888        */
/*                                                                              */
/*       A Three-Dimensional General Purpose Semiconductor Simulator.           */
/*                                                                              */
/*                                                                              */
/*  Copyright (C) 2007-2008                                                     */
/*  Cogenda Pte Ltd                                                             */
/*                                                                              */
/*  Please contact Cogenda Pte Ltd for license information                      */
/*                                                                              */
/*  Author: Gong Ding   gdiso@ustc.edu                                          */
/*                                                                              */
/********************************************************************************/

#ifndef __silvaco_h__
#define __silvaco_h__

#include <map>

#include "stanford.h"


/**
 * read silvaco TIF file
 */
class SilvacoTIF : public StanfordTIF
{
public:

  /**
   * constructor
   */
  SilvacoTIF(const std::string & file);

  /**
   * destroy internal data?
   */
  virtual ~SilvacoTIF() {}

  /**
   * read the silvaco tif file
   */
  virtual bool read();


  void export_scatter_doping_data() const;


private:

  std::vector<int>       _electrode_info;

  /**
   * implant map
   */
  std::map<int, std::string> SilImp;

  /**
   * material map
   */
  std::map<int, std::string> SilMat;

};

#endif // #define __silvaco_h__

