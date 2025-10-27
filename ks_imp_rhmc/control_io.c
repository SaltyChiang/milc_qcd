/************************* control.c *******************************/
/* MIMD version 7 */
/* Main procedure for SU3 with dynamical staggered fermions        */
/* general quark action, general gauge action */

/* This file is for lattice generation with the RHMC algorithm */

#define CONTROL
#include "ks_imp_includes.h" /* definitions files and prototypes */
#include "lattice_qdp.h"

#ifdef HAVE_QUDA
#include <quda_milc_interface.h>
#include "../include/generic_quda.h"
#endif

#ifdef HAVE_QPHIX
#include "../include/generic_qphix.h"
#endif

#ifdef MILC_GLOBAL_DEBUG
#include "debug.h"
#endif /* MILC_GLOBAL_DEBUG */

/* For information */
#define NULL_FP -1

EXTERN gauge_header start_lat_hdr; /* Input gauge field header */

int main(int argc, char **argv)
{
  int i, meascount, traj_done, naik_index;
  int prompt;
  int s_iters, avs_iters, avbcorr_iters;
  double starttime, endtime;
#ifdef PRTIME
  double dtime;
#endif

  initialize_machine(&argc, &argv);

  /* Remap standard I/O */
  if (remap_stdio_from_args(argc, argv) == 1)
    terminate(1);

  g_sync();

  starttime = dclock();

  /* set up */
  STARTTIME;
  prompt = setup();
  ENDTIME("setup");

  // const char *filename = "/scratch/07893/junjieli/milc/vista-large-scale-test/my-test/l192384f211b728m000415m01129m1329a.67";
  const char *filename = "../binary_samples/lat.sample.l8888";
  // const char *filename_out = "l192384f211b728m000415m01129m1329a.67";
  const char *filename_out = "lat.sample.l8888";

  startlat_p = reload_lattice(RELOAD_PARALLEL, filename);

  save_lattice(SAVE_PARALLEL, filename_out, stringLFN);

  startlat_p = reload_lattice(RELOAD_MPIIO, filename);

  save_lattice(SAVE_MPIIO, filename_out, stringLFN);

  free_lattice();

#ifdef HAVE_QUDA
  finalize_quda();
#endif

#ifdef HAVE_QPHIX
  finalize_qphix();
#endif

  normal_exit(0);
  return 0;
}
