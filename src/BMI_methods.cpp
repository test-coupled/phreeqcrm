// PhreeqcRM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <sstream>
#include "PhreeqcRM.h"
#include "IPhreeqc.h"
#include "IPhreeqcPhast.h"
#include "BMI_Var.h"
#ifdef USE_YAML
#include "yaml-cpp/yaml.h"
#endif
void PhreeqcRM::BMI_SetValue(std::string name, void* src)
{
    std::string name_lc = name;
    std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
    std::map < std::string, BMI_Var >::iterator it = this->bmi_var_map.find(name_lc);
    if (it != bmi_var_map.end())
    {
        if (it->first == "concentrations")
        {
            int ngrid = this->GetGridCellCount();
            int ncomps = this->GetComponentCount();
            std::vector<double> conc(ngrid * ncomps, INACTIVE_CELL_VALUE);
            memcpy(conc.data(), src, ngrid * ncomps * sizeof(double));
            this->SetConcentrations(conc);
            return;
        }
        if (it->first == "density")
        {
            int ngrid = this->GetGridCellCount();
            std::vector<double> density(ngrid, INACTIVE_CELL_VALUE);
            memcpy(density.data(), src, ngrid * sizeof(double));
            this->SetDensity(density);
            return;
        }
        if (it->first == "fileprefix")
        {
            std::string file = (char*) src;
            this->SetFilePrefix(file);
            return;
        }
        if (it->first == "nthselectedoutput")
        {
            int nth_so;
            memcpy(&nth_so, src, sizeof(int));
            int nuser = this->GetNthSelectedOutputUserNumber(nth_so);
            this->SetCurrentSelectedOutputUserNumber(nuser);
            return;
        }
        if (it->first == "porosity")
        {
            int ngrid = this->GetGridCellCount();
            std::vector<double> porosity(ngrid, INACTIVE_CELL_VALUE);
            memcpy(porosity.data(), src, ngrid * sizeof(double));
            this->SetPorosity(porosity);
            return;
        }
        if (it->first == "porosity")
        {
            int ngrid = this->GetGridCellCount();
            std::vector<double> porosity(ngrid, INACTIVE_CELL_VALUE);
            memcpy(porosity.data(), src, ngrid * sizeof(double));
            this->SetPorosity(porosity);
            return;
        }
        if (it->first == "pressure")
        {
            int ngrid = this->GetGridCellCount();
            std::vector<double> pressure(ngrid, INACTIVE_CELL_VALUE);
            memcpy(pressure.data(), src, ngrid * sizeof(double));
            this->SetPressure(pressure);
            return;
        }
        if (it->first == "saturation")
        {
            int ngrid = this->GetGridCellCount();
            std::vector<double> sat(ngrid, INACTIVE_CELL_VALUE);
            memcpy(sat.data(), src, ngrid * sizeof(double));
            this->SetSaturation(sat);
            return;
        }
        if (it->first == "selectedoutputon")
        {
            int so_on;
            memcpy(&so_on, src, sizeof(int));
            bool so_on_bool = (bool)so_on;
            this->SetSelectedOutputOn(so_on_bool);
            return;
        }
        if (it->first == "temperature")
        {
            int ngrid = this->GetGridCellCount();
            std::vector<double> temp(ngrid, INACTIVE_CELL_VALUE);
            memcpy(temp.data(), src, ngrid * sizeof(double));
            this->SetTemperature(temp);
            return;
        }
        if (it->first == "time")
        {
            double time;
            memcpy(&time, src, sizeof(double));
            this->SetTime(time);
            return;
        }
        if (it->first == "timestep")
        {
            double timestep=0;
            memcpy(&timestep, src, sizeof(double));
            this->SetTimeStep(timestep);
            return;
        }
    }
    //throw LetItThrow("Item not found");
    ErrorMessage("Item not found");
    throw PhreeqcRMStop();
}
void PhreeqcRM::BMI_GetValue(std::string name, void* dest)
{
    std::string name_lc = name;
    std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
    std::map < std::string, BMI_Var >::iterator it = this->bmi_var_map.find(name_lc);
    if (it != bmi_var_map.end())
    {
        if (it->first == "componentcount")
        {
            int count = this->GetComponentCount();
            memcpy(dest, &count, sizeof(int));
            return;
        }
        if (it->first == "components")
        {
            int string_length = this->BMI_GetVarItemsize("Components");
            std::vector<std::string> comps = this->GetComponents();
            std::stringstream all_comps;
            for (size_t i = 0; i < comps.size(); i++)
            {
                all_comps << std::left << std::setfill(' ') << std::setw(string_length) << comps[i];
            }
            memcpy(dest, all_comps.str().c_str(), all_comps.str().size());
            return;
        }
        if (it->first == "concentrations")
        {
            std::vector<double> rm_conc;
            this->GetConcentrations(rm_conc);
            memcpy(dest, rm_conc.data(), rm_conc.size()*sizeof(double));
            return;
        }
        if (it->first == "currentselectedoutputusernumber")
        {
            int count = this->GetIPhreeqcPointer(0)->GetCurrentSelectedOutputUserNumber();
            memcpy(dest, &count, sizeof(int));
            return;
        }
        if (it->first == "density")
        {
            std::vector<double> density;
            this->GetDensity(density);
            memcpy(dest, density.data(), density.size()*sizeof(double));
            return;
        }
        if (it->first == "fileprefix")
        {
            std::string filep = this->GetFilePrefix();
            memcpy(dest, filep.c_str(), filep.size());
            return;
        }
        if (it->first == "errorstring")
        {
            std::string err = this->GetErrorString();
            memcpy(dest, err.c_str(), err.size());
            return;
        }
        if (it->first == "gfw")
        {
            const std::vector<double> gfw = this->GetGfw();
            memcpy(dest, gfw.data(), gfw.size() * sizeof(double));
            return;
        }
        if (it->first == "gridcellcount")
        {
            int count = this->GetGridCellCount();
            memcpy(dest, &count, sizeof(int));
            return;
        }
        //if (it->first == "NthSelectedOutputUserNumber")
        //{
        //    int num = this->GetNthSelectedOutputUserNumber();
        //    memcpy(dest, &num, sizeof(int));
        //    return;
        //}
        if (it->first == "porosity")
        {
            const std::vector<double>& porosity = this->GetPorosity();
            memcpy(dest, porosity.data(), porosity.size() * sizeof(double));
            return;
        }
        if (it->first == "pressure")
        {
            const std::vector<double> &pressure = this->GetPressure();
            memcpy(dest, pressure.data(), pressure.size() * sizeof(double));
            return;
        }
        if (it->first == "saturation")
        {
            std::vector<double> saturation;
            this->GetSaturation(saturation);
            memcpy(dest, saturation.data(), saturation.size() * sizeof(double));
            return;
        }
        if (it->first == "selectedoutput")
        {
            std::vector<double> so;
            IRM_RESULT status = this->GetSelectedOutput(so);
            memcpy(dest, so.data(), so.size() * sizeof(double));
            return;
        }
        if (it->first == "selectedoutputcolumncount")
        {
            int count = this->GetSelectedOutputColumnCount();
            memcpy(dest, &count, sizeof(int));
            return;
        }
        if (it->first == "selectedoutputcount")
        {
            int count = this->GetSelectedOutputCount();
            memcpy(dest, &count, sizeof(int));
            return;
        }
        if (it->first == "selectedoutputheadings")
        {
            int string_length = this->BMI_GetVarItemsize("SelectedOutputHeadings");
            int count = this->GetSelectedOutputColumnCount();
            std::stringstream all_headings;
            for (int i = 0; i < count; i++)
            {
                std::string heading;
                IRM_RESULT status = this->GetSelectedOutputHeading(i, heading);
                all_headings << std::left << std::setfill(' ') << std::setw(string_length) << heading;
            }
            memcpy(dest, all_headings.str().c_str(), all_headings.str().size());
            return;
        }
        if (it->first == "selectedoutputon")
        {
            int flag = (int)this->GetSelectedOutputOn();
            memcpy(dest, &flag, sizeof(int));
            return;
        }
        if (it->first == "selectedoutputon")
        {
            bool tf = this->GetSelectedOutputOn();
            memcpy(dest, &tf, sizeof(bool));
            return;
        }
        if (it->first == "selectedoutputrowcount")
        {
            int count = this->GetSelectedOutputRowCount();
            memcpy(dest, &count, sizeof(int));
            return;
        }
        if (it->first == "solutionvolume")
        {
            const std::vector<double>& vol = this->GetSolutionVolume();
            memcpy(dest, vol.data(), vol.size() * sizeof(double));
            return;
        }
        if (it->first == "temperature")
        {
            const std::vector<double> &temperature = this->GetTemperature();
            memcpy(dest, temperature.data(), temperature.size() * sizeof(double));
            return;
        }
        if (it->first == "time")
        {
            double time = this->GetTime();
            memcpy(dest, &time, sizeof(double));
            return;
        }
        if (it->first == "timestep")
        {
            double timestep = this->GetTimeStep();
            memcpy(dest, &timestep, sizeof(double));
            return;
        }
    }
    //throw LetItThrow("Item not found");
    ErrorMessage("Item not found");
    throw PhreeqcRMStop();
}
int PhreeqcRM::BMI_GetVarNbytes(std::string name)
{
    std::string name_lc = name;
    std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
    std::map < std::string, BMI_Var >::iterator it = this->bmi_var_map.find(name_lc);
    if (it != bmi_var_map.end())
    {
        if (it->first == "componentcount")
        {
            return this->GetComponentCount();
        }
        if (it->first == "components")
        {
            int string_size = this->BMI_GetVarItemsize("components");
            int dim = this->GetComponentCount();
            return string_size * dim * (int)sizeof(char);
        }
        if (it->first == "concentrations")
        {
            return (int)sizeof(double) * this->GetGridCellCount() * this->GetComponentCount();
        }
        if (it->first == "currentselectedoutputusernumber")
        {
            return (int)sizeof(int);
        }
        if (it->first == "density")
        {
            return (int)sizeof(double) * this->GetGridCellCount();
        }

        if (it->first == "fileprefix")
        {
            return (int)this->GetFilePrefix().size();
        }
        if (it->first == "errorstring")
        {
            return (int)this->GetErrorString().size();
        }
        if (it->first == "gfw")
        {
            return (int)sizeof(double) * this->GetComponentCount();
        }
        if (it->first == "gridcellcount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "nthselectedoutput")
        {
            return (int)sizeof(int);
        }
        if (it->first == "porosity")
        {
            return (int)sizeof(double) * this->GetGridCellCount();
        }
        if (it->first == "pressure")
        {
            return (int)sizeof(double) * this->GetGridCellCount();
        }
        if (it->first == "saturation")
        {
            return (int)sizeof(double) * this->GetGridCellCount();
        }
        if (it->first == "selectedoutput")
        {
            return (int)sizeof(double) * this->GetSelectedOutputColumnCount() * this->GetSelectedOutputRowCount();
        }
        if (it->first == "selectedoutputcolumncount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "selectedoutputcount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "selectedoutputheadings")
        {
            int string_size = this->BMI_GetVarItemsize("selectedoutputheadings");
            return string_size * this->GetSelectedOutputColumnCount() * (int)sizeof(char);
        }
        if (it->first == "selectedoutputon")
        {
            return (int)sizeof(int);
        }
        if (it->first == "selectedoutputrowcount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "solutionvolume")
        {
            return (int)sizeof(double) * this->GetGridCellCount();
        }
        if (it->first == "temperature")
        {
            return (int)sizeof(double) * this->GetGridCellCount();
        }
    }
	//throw LetItThrow("Item not found");
    ErrorMessage("Item not found");
    throw PhreeqcRMStop();
}
std::string PhreeqcRM::BMI_GetVarUnits(std::string name)
{
    std::string name_lc = name;
    std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
    std::map < std::string, BMI_Var >::iterator it = this->bmi_var_map.find(name_lc);
    if (it != bmi_var_map.end())
    {
        if (it->first == "concentrations")
        {
            int units = this->GetUnitsSolution();
            switch (units)
            {
            case 1:
                return "mg L-1";
                break;
            case 2:
                return "mol L-1";
                    break;
            case 3:
                return "kg kgs-1";
				break;
			default:
				//throw LetItThrow("Unknown units for GetUnitsSolution in GetVarUnits");
                ErrorMessage("Unknown units for GetUnitsSolution in GetVarUnits");
                throw PhreeqcRMStop();
				break;
			}
        }
        return it->second.GetUnits();
    }
    //throw LetItThrow("Item not found");
    ErrorMessage("Item not found");
    throw PhreeqcRMStop();
}
int PhreeqcRM::BMI_GetVarItemsize(std::string name)
{
    std::string name_lc = name;
    std::transform(name_lc.begin(), name_lc.end(), name_lc.begin(), tolower);
    std::map < std::string, BMI_Var >::iterator it = this->bmi_var_map.find(name_lc);
    if (it != bmi_var_map.end())
    {
        if (it->first == "componentcount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "components")
        {
            size_t max = 0;
            for (size_t i = 0; i < this->GetComponents().size(); i++)
            {
                if (this->GetComponents()[i].size() > max) max = this->GetComponents()[i].size();
            }
            return (int)max;
        }
        if (it->first == "concentrations")
        {
            return (int)sizeof(double);
        }
        if (it->first == "currentselectedoutputusernumber")
        {
            return (int)sizeof(int);
        }
        if (it->first == "density")
		{
            return (int)sizeof(double);
		}
        if (it->first == "fileprefix")
        {
            return (int)this->GetFilePrefix().size();
        }
        if (it->first == "errorstring")
        {
            return (int)this->GetErrorString().size();
        }
        if (it->first == "gfw")
		{
            return (int)sizeof(double);
		}
        if (it->first == "gridcellcount")
		{
            return (int)sizeof(int);
		}
		if (it->first == "nthselectedoutput")
		{
            return (int)sizeof(int);
		}
		if (it->first == "porosity")
		{
            return (int)sizeof(double);
		}
        if (it->first == "pressure")
        {
            return (int)sizeof(double);
        }
        if (it->first == "saturation")
        {
            return (int)sizeof(double);
        }
        if (it->first == "selectedoutput")
        {
            return (int)sizeof(double);
        }
        if (it->first == "selectedoutputcolumncount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "selectedoutputcount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "selectedoutputheadings")
        {
            int nhead = this->GetSelectedOutputColumnCount();
            size_t max = 0;
            for (int i = 0; i < nhead; i++)
            {
                std::string heading;
                this->GetSelectedOutputHeading(i, heading);
                if (heading.size() > max) max = heading.size();
            }
            return (int)max;
        }
        if (it->first == "selectedoutputon")
        {
            return (int)sizeof(int);
        }
        if (it->first == "selectedoutputrowcount")
        {
            return (int)sizeof(int);
        }
        if (it->first == "solutionvolume")
        {
            return (int)sizeof(double);
        }
        if (it->first == "temperature")
        {
            return (int)sizeof(double);
        }
    }
    else
    {
        //throw LetItThrow("Item not found");
        ErrorMessage("Item not found");
        throw PhreeqcRMStop();
    }
    return -1;
}
std::string PhreeqcRM::BMI_GetVarType(std::string name)
{
    std::map < std::string, BMI_Var >::iterator it = this->bmi_var_map.find(name);
    if (it != bmi_var_map.end())
    {
        return it->second.GetType();
    }
    else
    {
        //throw LetItThrow("Item not found");
        ErrorMessage("Item not found");
        throw PhreeqcRMStop();
    }
}
void PhreeqcRM::BMI_MakeVarMap()
{
    //if (state >= 0)
    {
        //-1 before create
        //0  RM created
        //1  map created
        //2  PhreeqcInitial2module
        //var_map["ncells"] = Var_BMI("ncells", "int", "count", sizeof(int));
        //var_map["threads"] = Var_BMI("threads", "int", "count", sizeof(int));

        //var_map["BackwardMapping"] = Var_BMI("BackwardMapping", "int", "mapping", sizeof(int));
        //var_map["CreateMapping"] = Var_BMI("CreateMapping", "int", "mapping", sizeof(int));
        //var_map["ChemistryCellCount"] = Var_BMI("ChemistryCellCount", "int", "count", sizeof(int));
        bmi_var_map["components"] = BMI_Var("Components", "string", "names", false, true);
        bmi_var_map["componentcount"] = BMI_Var("Componentcount", "int", "names", false, true);
        bmi_var_map["concentrations"] = BMI_Var("Concentrations", "double", "mol L-1", true, true);
        bmi_var_map["density"] = BMI_Var("Density", "double", "kg L-1", true, true);
        //var_map["EndCell"] = Var_BMI("EndCell", "int", "cell numbers", sizeof(int));
        //var_map["EquilibriumPhasesNames"] = Var_BMI("EquilibriumPhasesNames", "string", "names", sizeof(char));
        bmi_var_map["errorstring"] = BMI_Var("ErrorString", "string", "error", false, true);
        //var_map["ExchangeNames"] = Var_BMI("ExchangeNames", "string", "names", sizeof(char));
        //var_map["ExchangeSpeciesNames"] = Var_BMI("ExchangeSpeciesNames", "string", "names", sizeof(char));
        bmi_var_map["fileprefix"] = BMI_Var("FilePrefix", "string", "name", true, true);
        //!var_map["GasComponentNames"] = Var_BMI("GasComponentsNames", "string", "names", sizeof(char));
        //!var_map["GasCompMoles"] = Var_BMI("GasCompMoles", "double", "mol", sizeof(double));
        //!var_map["GasCompPressures"] = Var_BMI("GasCompPressures", "double", "atm", sizeof(double));
        //!var_map["GasCompPhi"] = Var_BMI("GasCompPhi", "double", "atm-1", sizeof(double));
        //!var_map["GasPhaseVolume"] = Var_BMI("GasPhaseVolume", "double", "L", sizeof(double));
        bmi_var_map["gfw"] = BMI_Var("Gfw", "double", "g mol-1", false, true);
        bmi_var_map["gridcellcount"] = BMI_Var("GridCellCount", "int", "count", false, true);
        //var_map["KineticReactions"] = Var_BMI("KineticReactions", "string", "names", sizeof(char));
        //var_map["MpiMyself"] = Var_BMI("MpiMyself", "int", "id", sizeof(int));
        //var_map["MpiTasks"] = Var_BMI("MpiTasks", "int", "count", sizeof(int));
        bmi_var_map["nthselectedoutput"] = BMI_Var("NthSelectedOutput", "int", "id", true, false);
        bmi_var_map["saturation"] = BMI_Var("Saturation", "double", "unitless", true, true);
        bmi_var_map["selectedoutput"] = BMI_Var("SelectedOutput", "double", "user", false, true);
        bmi_var_map["selectedoutputcolumncount"] = BMI_Var("SelectedOutputColumnCount", "int", "count", false, true);
        bmi_var_map["selectedoutputcount"] = BMI_Var("SelectedOutputCount", "int", "count", false, true);
        bmi_var_map["selectedoutputheadings"] = BMI_Var("SelectedOutputHeadings", "string", "names", false, true);
        bmi_var_map["selectedoutputrowcount"] = BMI_Var("SelectedOutputRowCount", "int", "count", false, true);
        //var_map["SINames"] = Var_BMI("SINames", "string", "names", 0);
        //var_map["SolidSolutionComponentsNames"] = Var_BMI("SolidSolutionComponentsNames", "string", "names", sizeof(char));
        //var_map["SolidSolutionNames"] = Var_BMI("SolidSolutionNames", "string", "names", sizeof(char));
        bmi_var_map["solutionvolume"] = BMI_Var("SolutionVolume", "double", "L", false, true);
        //!var_map["SpeciesConcentrations"] = Var_BMI("SpeciesConcentrations", "double", "mg L-1", sizeof(double));
        //!var_map["SpeciesD25"] = Var_BMI("SpeciesD25", "double", "cm2 s-1", sizeof(double));
        //!var_map["SpeciesLog10Gammas"] = Var_BMI("SpeciesLog10Gammas", "double", "log L mol-1", sizeof(double));
        //!var_map["SpeciesLog10Molalities"] = Var_BMI("SpeciesLog10Molalities", "double", "log mol L-1", sizeof(double));
        //!var_map["SpeciesNames"] = Var_BMI("SpeciesNames", "string", "names", sizeof(char));
        //!var_map["SpeciesSaveOn"] = Var_BMI("SpeciesSaveOn", "int", "flag", sizeof(char));
        //!var_map["SpeciesZ"] = Var_BMI("SpeciesZ", "double", "charge number", sizeof(double));
        //var_map["StartCell"] = Var_BMI("StartCell", "int", "cell numbers", sizeof(int));
        //var_map["SurfaceNames"] = Var_BMI("SurfaceNames", "string", "names", sizeof(char));
        //var_map["SurfaceSpeciesNames"] = Var_BMI("SurfaceSpeciesNames", "string", "names", sizeof(char));
        //var_map["SurfaceTypes"] = Var_BMI("SurfaceTypes", "string", "names", sizeof(char));
        //var_map["ThreadCount"] = Var_BMI("ThreadCount", "int", "count", sizeof(int));
        bmi_var_map["time"] = BMI_Var("Time", "double", "s", true, true);
        //var_map["TimeConversion"] = Var_BMI("TimeConversion", "double", "unitless", sizeof(double));
        bmi_var_map["timestep"] = BMI_Var("TimeStep", "double", "s", true, true);
        //var_map["MpiWorker"] = Var_BMI("MpiWorker", "int", "id", sizeof(int));
        //var_map["ComponentH2O"] = Var_BMI("ComponentH2O", "int", "flag", sizeof(int));
        bmi_var_map["currentselectedoutputusernumber"] = BMI_Var("CurrentSelectedOutputUserNumber", "int", "id", false, true);
        //var_map["DumpFileName"] = Var_BMI("DumpFileName", "string", "name", sizeof(char));
        //var_map["ErrorHandlerMode"] = Var_BMI("ErrorHandlerMode", "int", "flag", sizeof(int));
        //var_map["ErrorOn"] = Var_BMI("ErrorOn", "int", "flag", sizeof(int));
        //var_map["PartitionUZSolids"] = Var_BMI("PartitionUZSolids", "int", "flag", sizeof(int));
        bmi_var_map["porosity"] = BMI_Var("Porosity", "double", "unitless", true, true);
        //var_map["PartitionUZSolids"] = Var_BMI("PartitionUZSolids", "int", "flag", sizeof(int));
        bmi_var_map["pressure"] = BMI_Var("Pressure", "double", "atm", true, true);
        //var_map["PrintChemistryMask"] = Var_BMI("PrintChemistryMask", "int", "flags", sizeof(int));
        //var_map["PrintChemistryOn"] = Var_BMI("PrintChemistryOn", "int", "flag", sizeof(int));
        //var_map["RebalanceByCell"] = Var_BMI("RebalanceByCell", "int", "flag", sizeof(int));
        //var_map["RebalanceFraction"] = Var_BMI("RebalanceFraction", "double", "unitless", sizeof(double));
        //var_map["RepresentativeVolume"] = Var_BMI("RepresentativeVolume", "double", "L", sizeof(double));
        //var_map["RebalanceByCell"] = Var_BMI("RebalanceByCell", "int", "flag", sizeof(int));
        //var_map["ScreenOn"] = Var_BMI("ScreenOn", "int", "flag", sizeof(int));
        bmi_var_map["selectedoutputon"] = BMI_Var("SelectedOutputOn", "int", "flag", true, true);
        bmi_var_map["temperature"] = BMI_Var("Temperature", "double", "C", true, true);
        //var_map["UnitsExchange"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UnitsGasPhase"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UnitsKinetics"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UnitsPPassemblage"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UnitsSolution"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UnitsSSassemblage"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UnitsSurface"] = Var_BMI("UnitsExchange", "int", "flag", sizeof(int));
        //var_map["UseSolutionDensityVolume"] = Var_BMI("UseSolutionDensityVolume", "int", "flag", sizeof(int));

    }
    this->bmi_input_vars.clear();
    this->bmi_output_vars.clear();
    std::map<std::string, class BMI_Var>::iterator it;
    for (it = bmi_var_map.begin(); it != bmi_var_map.end(); it++)
    {
        if (it->second.GetSet())
        {
            bmi_input_vars.push_back(it->first);
        }
        if (it->second.GetGet())
        {
            bmi_output_vars.push_back(it->first);
        }
    }
}
#ifdef USE_YAML
IRM_RESULT		PhreeqcRM::InitializeYAML(std::string config)
{
    YAML::Node yaml = YAML::LoadFile(config);
    std::string keyword;
    YAML::Node node; 
    for (YAML::Node::const_iterator it = yaml.begin();it != yaml.end();++it)
    {
        keyword = it->first.as<std::string>();
        YAML::Node node = it->second;
        if (keyword == "CloseFiles")
        {
            this->CloseFiles();
            continue;
        }
        if (keyword == "CreateMapping")
        {
            assert(node.IsSequence());
            std::vector<int> grid2chem = it->second.as<std::vector<int>>();
            this->CreateMapping(grid2chem);
            continue;
        }
        if (keyword == "DumpModule")
        {
            assert(node.IsMap());
            assert(node.size() == 2);
            YAML::const_iterator it1 = node.begin();
            bool dump_on = it1++->second.as<bool>();
            bool append = it1++->second.as<bool>();
            this->DumpModule(dump_on, append);
            continue;
        }
        if (keyword == "FindComponents")
        {
            this->FindComponents();
            continue;
        }
        if (keyword == "InitialPhreeqc2Module")
        {
            if (node.IsSequence())
            {
				std::vector< int > ic = node.as< std::vector< int > >();
				this->InitialPhreeqc2Module(ic);
				continue;
            }
			else if (node.IsMap())
			{
				assert(node.IsMap());
				assert(node.size() == 3);
				YAML::const_iterator it1 = node.begin();
				std::vector < int > ic1 = it1++->second.as< std::vector < int > >();
				std::vector < int > ic2 = it1++->second.as< std::vector < int > >();
				std::vector < double > f1 = it1->second.as< std::vector < double > >();
				this->InitialPhreeqc2Module(ic1, ic2, f1);
				continue;
	        }
            //throw LetItThrow("YAML argument mismatch InitialPhreeqc2Module");
            ErrorMessage("YAML argument mismatch InitialPhreeqc2Module");
            throw PhreeqcRMStop();
        }
        if (keyword == "InitialPhreeqcCell2Module")
        {
            assert(node.IsMap());
			assert(node.size() == 2);
			YAML::const_iterator it1 = node.begin();
			int n = it1++->second.as<int>();
			std::vector< int > cell_numbers = it1->second.as< std::vector<int > >();
            this->InitialPhreeqcCell2Module(n, cell_numbers);
            continue;
        }
		if (keyword == "LoadDatabase") 
        {
            std::string file = node.as< std::string >();
            this->LoadDatabase(file);
            continue;
        }
		if (keyword == "OpenFiles") 
        {
            this->OpenFiles();
            continue;
        }
		if (keyword == "OutputMessage") 
        {
            assert(node.IsScalar());
            std::string str = node.as< std::string >();
            this->OutputMessage(str);
            continue;
        }
		if (keyword == "RunCells") 
        {
            this->RunCells();
            continue;
        }
		if (keyword == "RunFile") 
        {
            assert(node.IsMap());
            assert(node.size() == 4);
            YAML::const_iterator it1 = node.begin();
            bool workers = it1++->second.as<bool>();
            bool initial = it1++->second.as<bool>();
            bool utility = it1++->second.as<bool>();
            std::string  file = it1->second.as< std::string >();
            this->RunFile(workers, initial, utility, file);
            continue;
        }
		if (keyword == "RunString") 
        {
            assert(node.IsMap());
            assert(node.size() == 4);
            YAML::const_iterator it1 = node.begin();
            bool workers = it1++->second.as<bool>();
            bool initial = it1++->second.as<bool>();
            bool utility = it1++->second.as<bool>();
            std::string  string = it1->second.as<std::string>();
            this->RunString(workers, initial, utility, string);
            continue;
        }
		if (keyword == "ScreenMessage") 
        {
            assert(node.IsScalar());
            std::string str = node.as< std::string >();
            this->ScreenMessage(str);
            continue;
        }
		if (keyword == "SetComponentH2O") 
        {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->SetComponentH2O(tf);
            continue;
		}
		if (keyword == "SetConcentrations") {
            assert(node.IsSequence());
            std::vector< double > c = node.as< std::vector< double > >();
            this->SetConcentrations(c);
			continue;
		}
		if (keyword == "SetCurrentSelectedOutputUserNumber") 
        {
            assert(node.IsScalar());
            int n = node.as< int >();
            this->SetCurrentSelectedOutputUserNumber(n);
			continue;
        }
		if (keyword == "SetDensity") 
        {
            assert(node.IsSequence());
            std::vector< double > den = node.as< std::vector< double > >();
            this->SetDensity(den);
            continue;
        }
		if (keyword == "SetDumpFileName") 
        {
            assert(node.IsScalar());
            std::string str = node.as< std::string >();
            this->SetDumpFileName(str);
            continue;
        }
		if (keyword == "SetErrorHandlerMode") 
        {
            assert(node.IsScalar());
            int mode = node.as< int >();
            this->SetErrorHandlerMode(mode);
            continue;
        }
		if (keyword == "SetErrorOn") {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->SetErrorOn(tf);
            continue;
        }
		if (keyword == "SetFilePrefix") 
        {
            assert(node.IsScalar());
            std::string prefix = node.as< std::string >();
            this->SetFilePrefix(prefix);
            continue;
        }
		if (keyword == "SetGasCompMoles") {
            assert(node.IsSequence());
            std::vector<double> mol = node.as< std::vector < double > >();
            this->SetGasCompMoles(mol);
            continue;
        }
		if (keyword == "SetGasPhaseVolume") {
            assert(node.IsSequence());
            std::vector<double> vol = node.as< std::vector < double > >();
            this->SetGasPhaseVolume(vol);
            continue;
        }
        if (keyword == "SetGridCellCount") {
            this->WarningMessage("SetGridCellCount has no effect after the PhreeqcRM instance is created.");
            continue;
        }
		if (keyword == "SetPartitionUZSolids") 
        {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->SetPartitionUZSolids(tf);
            continue;
        }
		if (keyword == "SetPorosity") 
        {
			assert(node.IsSequence());
			std::vector<double> por = node.as< std::vector< double > >();
            this->SetPorosity(por);
            continue;
        }
		if (keyword == "SetPressure") 
        {
			assert(node.IsSequence());
			std::vector<double> pressure = node.as< std::vector< double > >();
            this->SetPressure(pressure);
            continue;
        }
		if (keyword == "SetPrintChemistryMask") 
        {
            assert(node.IsSequence());
            std::vector<int> mask = node.as< std::vector< int > >();
            this->SetPrintChemistryMask(mask);
            continue;
        }
		if (keyword == "SetPrintChemistryOn") 
        {
            assert(node.IsMap());
            assert(node.size() == 3);
            YAML::const_iterator it1 = node.begin();
            bool workers = it1++->second.as< bool >();
            bool initial = it1++->second.as< bool >();
            bool utility = it1->second.as< bool >();
            this->SetPrintChemistryOn(workers, initial, utility);
            continue;
        }
		if (keyword == "SetRebalanceByCell") 
        {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->SetRebalanceByCell(tf);
            continue;
        }
		if (keyword == "SetRebalanceFraction") 
        {
            assert(node.IsScalar());
            double f = node.as<double>();
            this->SetRebalanceFraction(f);
            continue;
        }
		if (keyword == "SetRepresentativeVolume") 
        {
            assert(node.IsSequence());
            std::vector<double> rv = it->second.as< std::vector<double > >();
            this->SetRepresentativeVolume(rv);
            continue;
        }
		if (keyword == "SetSaturation") 
        {
            assert(node.IsSequence());
            std::vector< double > sat = node.as< std::vector< double> >();
            this->SetSaturation(sat);
            continue;
        }
		if (keyword == "SetScreenOn") {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->SetScreenOn(tf);
            continue;
        }
		if (keyword == "SetSelectedOutputOn") 
        {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->SetSelectedOutputOn(tf);
            continue;
        }
		if (keyword == "SetSpeciesSaveOn") 
        {
            assert(node.IsScalar());
            bool tf = node.as< bool >(); 
            this->SetSpeciesSaveOn(tf);
            continue;
        }
		if (keyword == "SetTemperature") 
        {
            assert(node.IsSequence());
            std::vector<double> temp = node.as<std::vector<double>>();
            this->SetTemperature(temp);
            continue;
        }
		if (keyword == "SetTime") 
        {
            assert(node.IsScalar());
            double time = node.as<double>();
            this->SetTime(time);
            continue;
        }
		if (keyword == "SetTimeConversion") 
        {
            assert(node.IsScalar());
            double time_conv = node.as<double>();
            this->SetTimeConversion(time_conv);
            continue;
        }
		if (keyword == "SetTimeStep") 
        {
            assert(node.IsScalar());
            double time_step = node.as<double>();
            this->SetTimeStep(time_step);
            continue;
        }
		if (keyword == "SetUnitsExchange") 
        {
            assert(node.IsScalar());
            int units = node.as<int>();
            this->SetUnitsExchange(units);
            continue;
        }
		if (keyword == "SetUnitsGasPhase") 
        {
            assert(node.IsScalar());
            int units = node.as< int >();
            this->SetUnitsGasPhase(units);
            continue;
        }
		if (keyword == "SetUnitsKinetics") 
        {
            assert(node.IsScalar());
            int units = node.as< int >();
            this->SetUnitsKinetics(units);
            continue;
        }
		if (keyword == "SetUnitsPPassemblage") 
        {
            assert(node.IsScalar());
            int units = node.as< int >();
            this->SetUnitsPPassemblage(units);
            continue;
        }
		if (keyword == "SetUnitsSolution") 
        {
            assert(node.IsScalar());
            int units = node.as< int >();
            this->SetUnitsSolution(units);
            continue;
        }
		if (keyword == "SetUnitsSSassemblage") 
        {
            assert(node.IsScalar());
            int units = node.as< int >();
            this->SetUnitsSSassemblage(units);
            continue;
        }
		if (keyword == "SetUnitsSurface") 
        {
            assert(node.IsScalar());
            int units = node.as< int >();
            this->SetUnitsSurface(units);
            continue;
        }
		if (keyword == "SpeciesConcentrations2Module") 
        {
            assert(node.IsSequence());
            std::vector < double > scond = node.as< std::vector < double > >();
            this->SpeciesConcentrations2Module(scond);
            continue;
        }
		if (keyword == "StateSave") 
        {
            assert(node.IsScalar());
            int n = node.as< int >();
            this->StateSave(n);
            continue;
        }
		if (keyword == "StateApply") 
        {
            assert(node.IsScalar());
            int n = node.as< int >();
            this->StateApply(n);
            continue;
        }
		if (keyword == "StateDelete") 
        {
            assert(node.IsScalar());
            int n = node.as< int >();
            this->StateDelete(n);
            continue;
        }
		if (keyword == "UseSolutionDensityVolume") 
        {
            assert(node.IsScalar());
            bool tf = node.as< bool >();
            this->UseSolutionDensityVolume(tf);
            continue;
        }
		if (keyword == "WarningMessage") 
        {
            assert(node.IsScalar());
            std::string str = node.as< std::string >();
            this->WarningMessage(str);
            continue;
        }
		//throw LetItThrow("YAML keyword not found");
        ErrorMessage("YAML keyword not found");
        throw PhreeqcRMStop();
	}
    return IRM_RESULT::IRM_OK;
}
// Global method
int 
GetGridCellCountYAML(const char* YAML_file)
{
    YAML::Node yaml = YAML::LoadFile(YAML_file);
    std::string keyword;
    YAML::Node node;
    if (yaml["SetGridCellCount"].IsDefined())
    {
        return yaml["SetGridCellCount"].as<int>();
    }
    return 0;
}
#endif



