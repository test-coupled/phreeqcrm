///*! @file RM_interface_F.h
//	@brief C/Fortran Documentation
//*/
#ifndef RMF_INTERFACE_F_H
#define RMF_INTERFACE_F_H

#include "irm_dll_export.h"

#if defined(__cplusplus)
extern "C" {
#endif
IRM_DLL_EXPORT IRM_RESULT RMF_Abort(int *id, int *result, const char * err_str);
IRM_DLL_EXPORT IRM_RESULT RMF_CloseFiles(int *id);
IRM_DLL_EXPORT int        RMF_Concentrations2Utility(int *id, double *c, int *n, double *tc, double *p_atm);
IRM_DLL_EXPORT int        RMF_Create(int *nxyz, int *nthreads = NULL);
IRM_DLL_EXPORT IRM_RESULT RMF_CreateMapping (int *id, int *grid2chem); 
IRM_DLL_EXPORT IRM_RESULT RMF_DecodeError (int *id, int *e); 
IRM_DLL_EXPORT IRM_RESULT RMF_Destroy(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_DumpModule(int *id, int *dump_on, int *append);
IRM_DLL_EXPORT IRM_RESULT RMF_ErrorMessage(int *id, const char *err_str);
IRM_DLL_EXPORT int        RMF_FindComponents(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetBackwardMapping(int *id, int *n, int *list, int *size);
IRM_DLL_EXPORT int        RMF_GetChemistryCellCount(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetComponent(int * id, int * num, char *chem_name, int *l1);
IRM_DLL_EXPORT int        RMF_GetComponentCount(int * id);
IRM_DLL_EXPORT int        RMF_GetCurrentSelectedOutputUserNumber(int* id);
IRM_DLL_EXPORT int        RMF_GetExchangeSpeciesCount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetExchangeSpeciesName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT IRM_RESULT RMF_GetExchangeName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT int        RMF_GetSurfaceSpeciesCount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSurfaceSpeciesName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSurfaceType(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSurfaceName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT int        RMF_GetEquilibriumPhasesCount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetEquilibriumPhasesName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT int        RMF_GetGasComponentsCount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetGasComponentsName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT int        RMF_GetKineticReactionsCount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetKineticReactionsName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT int        RMF_GetSolidSolutionComponentsCount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSolidSolutionComponentsName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSolidSolutionName(int * id, int * num, char *name, int *l1);
IRM_DLL_EXPORT int        RMF_GetSICount(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSIName(int * id, int * num, char *name, int *l1);

IRM_DLL_EXPORT IRM_RESULT RMF_GetConcentrations(int *id, double *c);

IRM_DLL_EXPORT IRM_RESULT RMF_GetIthConcentration(int* id, int* i, double* c);
IRM_DLL_EXPORT IRM_RESULT RMF_GetIthSpeciesConcentration(int* id, int* i, double* c);
IRM_DLL_EXPORT IRM_RESULT RMF_SetIthConcentration(int* id, int* i, double* c);
IRM_DLL_EXPORT IRM_RESULT RMF_SetIthSpeciesConcentration(int* id, int* i, double* c);

IRM_DLL_EXPORT IRM_RESULT RMF_GetDensityCalculated(int *id, double *density);
IRM_DLL_EXPORT IRM_RESULT RMF_GetEndCell(int *id, int *ec);
IRM_DLL_EXPORT IRM_RESULT RMF_GetErrorString(int *id, char *prefix, int *l);
IRM_DLL_EXPORT int        RMF_GetErrorStringLength(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetFilePrefix(int *id, char *prefix, int *l);
IRM_DLL_EXPORT IRM_RESULT RMF_GetGasCompMoles(int *id, double *m);
IRM_DLL_EXPORT IRM_RESULT RMF_GetGasCompPressures(int* id, double* p);
IRM_DLL_EXPORT IRM_RESULT RMF_GetGasCompPhi(int* id, double* phi);
IRM_DLL_EXPORT IRM_RESULT RMF_GetGasPhaseVolume(int* id, double* v);
IRM_DLL_EXPORT IRM_RESULT RMF_GetGfw(int *id, double * gfw);
#ifdef USE_YAML
IRM_DLL_EXPORT int        RMF_GetGridCellCountYAML(const char* config_file);
#endif
IRM_DLL_EXPORT int        RMF_GetGridCellCount(int *id);
IRM_DLL_EXPORT int        RMF_GetIPhreeqcId(int *id, int *i);
IRM_DLL_EXPORT int        RMF_GetMpiMyself(int *id);
IRM_DLL_EXPORT int        RMF_GetMpiTasks(int *id);
IRM_DLL_EXPORT int        RMF_GetNthSelectedOutputUserNumber(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_GetPorosity(int* id, double* porosity);
IRM_DLL_EXPORT IRM_RESULT RMF_GetPressure(int* id, double* pressure);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSaturationCalculated(int *id, double *sat);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSelectedOutput(int *id, double *so);
IRM_DLL_EXPORT int        RMF_GetSelectedOutputColumnCount(int *id);
IRM_DLL_EXPORT int        RMF_GetSelectedOutputCount(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSelectedOutputHeading(int *id, int * icol, char * heading, int *length);
IRM_DLL_EXPORT int        RMF_GetSelectedOutputRowCount(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSolutionVolume(int *id, double *solution_volume);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSpeciesConcentrations(int *id, double *species_conc);
IRM_DLL_EXPORT int        RMF_GetSpeciesCount(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSpeciesD25(int *id, double *diffc);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSpeciesLog10Gammas(int *id, double *species_log10gammas);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSpeciesLog10Molalities(int* id, double* species_log10molalities);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSpeciesName(int *id, int *i, char * name, int *length);
IRM_DLL_EXPORT int        RMF_GetSpeciesSaveOn(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_GetSpeciesZ(int *id, double *z);
IRM_DLL_EXPORT IRM_RESULT RMF_GetStartCell(int *id, int *sc);
IRM_DLL_EXPORT IRM_RESULT RMF_GetTemperature(int* id, double* temperature);
IRM_DLL_EXPORT int        RMF_GetThreadCount(int *id);
IRM_DLL_EXPORT double     RMF_GetTime(int *id);
IRM_DLL_EXPORT double     RMF_GetTimeConversion(int *id);
IRM_DLL_EXPORT double     RMF_GetTimeStep(int *id);
//IRM_DLL_EXPORT int        RMF_GetVarItemsize(int* id, const char* str);
//IRM_DLL_EXPORT int        RMF_GetVarNbytes(int* id, const char* str);
IRM_DLL_EXPORT IRM_RESULT RMF_GetViscosity(int* id, double* viscosity);
#ifdef USE_YAML
IRM_DLL_EXPORT IRM_RESULT RMF_InitializeYAML(int* id, const char* yaml_name);
#endif
IRM_DLL_EXPORT IRM_RESULT RMF_InitialPhreeqc2Concentrations(
                int *id,
                double *c,
                int *n_boundary,
                int *boundary_solution1);
IRM_DLL_EXPORT IRM_RESULT RMF_InitialPhreeqc2Concentrations2(
                int *id,
                double *c,
                int *n_boundary,
                int *boundary_solution1,  
                int *boundary_solution2 = NULL, 
                double *fraction1 = NULL);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialSolutions2Module(int* id, int* in);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialEquilibriumPhases2Module(int* id, int* in);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialExchanges2Module(int* id, int* in);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialSurfaces2Module(int* id, int* in);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialGasPhases2Module(int* id, int* in);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialSolidSolutions2Module(int* id, int* in);
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialKinetics2Module(int *id, int* in);
IRM_DLL_EXPORT IRM_RESULT RMF_InitialPhreeqc2Module(int *id,
                int *initial_conditions1);		        // 7 x nxyz end-member 1
IRM_DLL_EXPORT  IRM_RESULT RMF_InitialPhreeqc2ModuleMix(int *id,
                int *initial_conditions1,		        // 7 x nxyz end-member 1
                int *initial_conditions2 = NULL,		// 7 x nxyz end-member 2
                double *fraction1 = NULL);			    // 7 x nxyz fraction of end-member 1
IRM_DLL_EXPORT IRM_RESULT RMF_InitialPhreeqcCell2Module(int *id,
                int *n,		                            // InitialPhreeqc cell number
                int *module_numbers,		            // Module cell numbers
                int *dim_module_numbers);			    // Number of module cell numbers
IRM_DLL_EXPORT IRM_RESULT RMF_InitialPhreeqc2SpeciesConcentrations(
                int *id,
                double *species_c,
                int *n_boundary,
                int *boundary_solution1);
IRM_DLL_EXPORT IRM_RESULT RMF_InitialPhreeqc2SpeciesConcentrations2(
                int *id,
                double *species_c,
                int *n_boundary,
                int *boundary_solution1,  
                int *boundary_solution2 = NULL, 
                double *fraction1 = NULL);
IRM_DLL_EXPORT IRM_RESULT RMF_LoadDatabase(int *id, const char *db_name);
IRM_DLL_EXPORT IRM_RESULT RMF_LogMessage(int * id, const char *str);
IRM_DLL_EXPORT IRM_RESULT RMF_MpiWorker(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_MpiWorkerBreak(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_OpenFiles(int * id);
IRM_DLL_EXPORT IRM_RESULT RMF_OutputMessage(int *id, const char * err_str);
IRM_DLL_EXPORT IRM_RESULT RMF_RunCells(int *id);
IRM_DLL_EXPORT IRM_RESULT RMF_RunFile(int *id, int * workers, int *initial_phreeqc, int *utility, const char *chem_name);
IRM_DLL_EXPORT IRM_RESULT RMF_RunString(int *id, int * workers, int *initial_phreeqc, int *utility, const char * input_string);
IRM_DLL_EXPORT IRM_RESULT RMF_ScreenMessage(int *id, const char *str);
IRM_DLL_EXPORT IRM_RESULT RMF_SetComponentH2O(int *id, int *tf);
IRM_DLL_EXPORT IRM_RESULT RMF_SetConcentrations(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetCurrentSelectedOutputUserNumber(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetDensityUser(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetDumpFileName(int *id, const char *dump_name);
IRM_DLL_EXPORT IRM_RESULT RMF_SetErrorHandlerMode(int *id, int *mode);
IRM_DLL_EXPORT IRM_RESULT RMF_SetErrorOn(int* id, int* t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetFilePrefix(int *id, const char *prefix);
IRM_DLL_EXPORT IRM_RESULT RMF_SetGasCompMoles(int *id, double *m);
IRM_DLL_EXPORT IRM_RESULT RMF_SetGasPhaseVolume(int* id, double* v);
IRM_DLL_EXPORT IRM_RESULT RMF_SetMpiWorkerCallback(int *id, int (*fcn)(int *x1));
IRM_DLL_EXPORT IRM_RESULT RMF_SetNthSelectedOutput(int* id, int* n);
IRM_DLL_EXPORT IRM_RESULT RMF_SetPartitionUZSolids(int *id, int *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetPorosity(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetPressure(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetPrintChemistryMask(int *id, int *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetPrintChemistryOn(int *id, int *worker, int *ip, int *utility);
IRM_DLL_EXPORT IRM_RESULT RMF_SetRebalanceByCell(int *id, int *method);
IRM_DLL_EXPORT IRM_RESULT RMF_SetRebalanceFraction(int *id, double *f);
IRM_DLL_EXPORT IRM_RESULT RMF_SetRepresentativeVolume(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetSaturationUser(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetScreenOn(int *id, int *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetSelectedOutputOn(int *id, int *selected_output);
IRM_DLL_EXPORT IRM_RESULT RMF_SetSpeciesSaveOn(int *id, int *save_on);
IRM_DLL_EXPORT IRM_RESULT RMF_SetTemperature(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetTime(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetTimeConversion(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetTimeStep(int *id, double *t);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsExchange(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsGasPhase(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsKinetics(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsPPassemblage(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsSolution(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsSSassemblage(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SetUnitsSurface(int *id, int *i);
IRM_DLL_EXPORT IRM_RESULT RMF_SpeciesConcentrations2Module(int *id, double * species_conc);
IRM_DLL_EXPORT IRM_RESULT RMF_StateSave(int* id, int* istate);
IRM_DLL_EXPORT IRM_RESULT RMF_StateApply(int* id, int* istate);
IRM_DLL_EXPORT IRM_RESULT RMF_StateDelete(int* id, int* istate);
IRM_DLL_EXPORT IRM_RESULT RMF_UseSolutionDensityVolume(int *id, int *tf);
IRM_DLL_EXPORT IRM_RESULT RMF_WarningMessage(int *id, const char *warn_str);

#if defined(__cplusplus)
}
#endif

#endif // RMF_INTERFACE_F_H
