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


#ifndef __pml_region_h__
#define __pml_region_h__

#include <vector>
#include <string>
#include "fvm_node_info.h"
#include "fvm_node_data_pml.h"
#include "fvm_cell_data_pml.h"
#include "material.h"
#include "simulation_region.h"

class Elem;

/**
 * the data and support function for PML
 */
class PMLSimulationRegion :  public SimulationRegion
{
public:

  /**
   * constructor
   */
  PMLSimulationRegion(const std::string &name, const std::string &material, SimulationSystem & system);

  /**
   * destructor
   */
  virtual ~PMLSimulationRegion()
  { delete mt; }

  /**
   * @return the region type
   */
  virtual SimulationRegionType type() const
  { return PMLRegion; }

  /**
   * insert local mesh element into the region, only copy the pointer
   * and create cell data
   */
  virtual void insert_cell (const Elem * e);

  /**
   * @note only node belongs to current processor and ghost node
   * own FVM_NodeData
   */
  virtual void insert_fvm_node(FVM_Node * fn)
  {

    // node (or ghost node) belongs to this processor
    // we should build FVM_NodeData structure for it

    if  ( fn->root_node()->on_local() )
      fn->hold_node_data( new FVM_PML_NodeData );

    _region_node[fn->root_node()->id()] = fn;
  }

  /**
   * init node data for this region
   */
  virtual void init(PetscScalar T_external);

  /**
   * re-init region data after import solution from data file
   */
  virtual void reinit_after_import();

  /**
   * @return the pointer to material data
   */
  Material::MaterialPML * material() const
  {return mt;}


  /**
   * @return the base class of material database
   */
  virtual Material::MaterialBase * get_material_base()
  { return (Material::MaterialBase *)mt; }

  /**
   * @return relative permittivity of material
   */
  virtual double get_eps() const
  { return mt->basic->Permittivity(); }

  /**
   * @return maretial density [g cm^-3]
   */
  virtual double get_density(PetscScalar T) const
  { return mt->basic->Density(T); }

  /**
   * get atom fraction of region material
   */
  virtual void atom_fraction(std::vector<std::string> &atoms, std::vector<double> & fraction) const
  {
    atoms.clear();
    fraction.clear();
    mt->basic->atom_fraction(atoms, fraction);
  }

private:
  /**
   * the pointer to material database
   */
  Material::MaterialPML *mt;


public:

  //////////////////////////////////////////////////////////////////////////////////////////////
  //----------------Function and Jacobian evaluate for Poisson's Equation---------------------//
  //////////////////////////////////////////////////////////////////////////////////////////////

  /**
   * filling solution data from FVM_NodeData into petsc vector of poisson's equation.
   */
  virtual void Poissin_Fill_Value(Vec , Vec ) {}

  /**
   * build function and its jacobian for poisson solver
   */
  virtual void Poissin_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build function and its jacobian for poisson solver
   */
  virtual void Poissin_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for poisson solver (experimental)
   */
  virtual void Poissin_Function_Hanging_Node(PetscScalar * , Vec , InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for poisson solver (experimental)
   */
  virtual void Poissin_Jacobian_Hanging_Node(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * update solution data of FVM_NodeData by petsc vector of poisson's equation.
   */
  virtual void Poissin_Update_Solution(PetscScalar *) {}


  //////////////////////////////////////////////////////////////////////////////////
  //----------------Function and Jacobian evaluate for L1 DDM---------------------//
  //////////////////////////////////////////////////////////////////////////////////

  /**
   * filling solution data from FVM_NodeData into petsc vector of L1 DDM.
   */
  virtual void DDM1_Fill_Value(Vec , Vec ) {}

  /**
   * build function and its jacobian for L1 DDM
   */
  virtual void DDM1_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build function and its jacobian for L1 DDM
   */
  virtual void DDM1_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L1 DDM, do nothing here
   */
  virtual void DDM1_Time_Dependent_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L1 DDM, do nothing here
   */
  virtual void DDM1_Time_Dependent_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L1 DDM (experimental)
   */
  virtual void DDM1_Function_Hanging_Node(PetscScalar * , Vec , InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L1 DDM (experimental)
   */
  virtual void DDM1_Jacobian_Hanging_Node(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * update solution data of FVM_NodeData by petsc vector of L1 DDM.
   */
  virtual void DDM1_Update_Solution(PetscScalar *) {}


  //////////////////////////////////////////////////////////////////////////////////
  //--------------Function and Jacobian evaluate for L1 HALL DDM------------------//
  //////////////////////////////////////////////////////////////////////////////////

  /**
   * filling solution data from FVM_NodeData into petsc vector of L1 HALL DDM.
   */
  virtual void HALL_Fill_Value(Vec , Vec ) {}

  /**
   * build function and its jacobian for L1 HALL DDM
   */
  virtual void HALL_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build function and its jacobian for L1 HALL DDM
   */
  virtual void HALL_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L1 HALL DDM (experimental)
   */
  virtual void HALL_Function_Hanging_Node(PetscScalar * , Vec , InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L1 HALL DDM (experimental)
   */
  virtual void HALL_Jacobian_Hanging_Node(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L1 HALL DDM
   */
  virtual void HALL_Time_Dependent_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L1 HALL DDM
   */
  virtual void HALL_Time_Dependent_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * update solution data of FVM_NodeData by petsc vector of L1 HALL DDM
   */
  virtual void HALL_Update_Solution(PetscScalar *) {}



  //////////////////////////////////////////////////////////////////////////////////
  //----------------Function and Jacobian evaluate for L2 DDM---------------------//
  //////////////////////////////////////////////////////////////////////////////////

  /**
   * filling solution data from FVM_NodeData into petsc vector of L2 DDM.
   */
  virtual void DDM2_Fill_Value(Vec , Vec ) {}

  /**
   * build function and its jacobian for L2 DDM
   */
  virtual void DDM2_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build function and its jacobian for L2 DDM
   */
  virtual void DDM2_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L2 DDM
   */
  virtual void DDM2_Time_Dependent_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L2 DDM
   */
  virtual void DDM2_Time_Dependent_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L2 DDM (experimental)
   */
  virtual void DDM2_Function_Hanging_Node(PetscScalar * , Vec , InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L2 DDM (experimental)
   */
  virtual void DDM2_Jacobian_Hanging_Node(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * update solution data of FVM_NodeData by petsc vector of L2 DDM.
   */
  virtual void DDM2_Update_Solution(PetscScalar *) {}


  //////////////////////////////////////////////////////////////////////////////////
  //----------------Function and Jacobian evaluate for L3 EBM---------------------//
  //////////////////////////////////////////////////////////////////////////////////

  /**
   * get nodal variable number, which depedent on EBM Level
   */
  virtual unsigned int ebm_n_variables() const { return 0; }

  /**
   * get offset of nodal variable, which depedent on EBM Level
   */
  virtual unsigned int ebm_variable_offset(SolutionVariable ) const { return 0; }

  /**
   * filling solution data from FVM_NodeData into petsc vector of L3 EBM.
   */
  virtual void EBM3_Fill_Value(Vec , Vec ) {}

  /**
   * build function and its jacobian for L3 EBM
   */
  virtual void EBM3_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build function and its jacobian for L3 EBM
   */
  virtual void EBM3_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L3 EBM (experimental)
   */
  virtual void EBM3_Function_Hanging_Node(PetscScalar * , Vec , InsertMode &) {}

  /**
   * process function and its jacobian at hanging node for L3 EBM (experimental)
   */
  virtual void EBM3_Jacobian_Hanging_Node(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L3 EBM
   */
  virtual void EBM3_Time_Dependent_Function(PetscScalar * , Vec , InsertMode &) {}

  /**
   * build time derivative term and its jacobian for L3 EBM
   */
  virtual void EBM3_Time_Dependent_Jacobian(PetscScalar * , Mat *, InsertMode &) {}

  /**
   * update solution data of FVM_NodeData by petsc vector of L3 EBM.
   */
  virtual void EBM3_Update_Solution(PetscScalar *) {}


  //////////////////////////////////////////////////////////////////////////////////
  //-----------------   Vec and Matrix evaluate for EBM AC   ---------------------//
  //////////////////////////////////////////////////////////////////////////////////

  /**
   * filling solution data from FVM_NodeData into petsc vector of DDMAC.
   */
  virtual void DDMAC_Fill_Value(Vec , Vec ) const {}

  /**
   * fill matrix of DDMAC equation
   */
  virtual void DDMAC_Fill_Matrix_Vector(Mat ,  Vec , const Mat , const double , InsertMode &) const {}

  /**
   * fill matrix of DDMAC equation for fvm_node
   */
  virtual void DDMAC_Fill_Nodal_Matrix_Vector(const FVM_Node *, Mat , Vec , const Mat , const double , InsertMode & ,
                                              const SimulationRegion * =NULL, const FVM_Node * =NULL) const {}

  /**
   * fill matrix of DDMAC equation for variable of fvm_node
   */
  virtual void DDMAC_Fill_Nodal_Matrix_Vector(const FVM_Node *, const SolutionVariable ,
                                              Mat , Vec , const Mat , const double , InsertMode & ,
                                              const SimulationRegion * =NULL, const FVM_Node * =NULL) const {}

  /**
   * update solution value of DDMAC equation
   */
  virtual void DDMAC_Update_Solution(PetscScalar *) {}
};




#endif //#ifndef __pml_region_h__