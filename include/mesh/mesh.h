#ifndef __mesh_h__
#define __mesh_h__

#include <map>
#include <vector>

#include "serial_mesh.h"
typedef SerialMesh DefaultMesh;


#include "fvm_node_info.h"


class SolverSystem;

/**
 * The \p Mesh class is a thin wrapper, around the \p SerialMesh class
 * by default.
*/

// ------------------------------------------------------------
// Mesh class definition
class Mesh : public DefaultMesh
{
 public:

  /**
   * Constructor.  Requires the dimension and optionally
   * a processor id.  Note that \p proc_id should always
   * be provided for multiprocessor applications.
   */
  Mesh (unsigned int d) : DefaultMesh(d) {}

  /**
   * Copy-constructor.  This should be able to take a
   * serial or parallel mesh.
   */
  Mesh (const UnstructuredMesh& other_mesh) : DefaultMesh(other_mesh) {}

  /**
   * Destructor.
   */
  ~Mesh() {}
  
  
private:
  
  friend class SolverSystem;
   
};





#endif
