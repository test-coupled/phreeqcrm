#if !defined(SOLUTION_H_INCLUDED)
#define SOLUTION_H_INCLUDED

#include <cassert>				// assert
#include <map>					// std::map
#include <string>				// std::string
#include <vector>				// std::vector
#include <iostream>
#include "Phreeqc_class.h"
#include "NumKeyword.h"
#include "SolutionIsotopeList.h"
#include "NameDouble.h"
class cxxMix;

class cxxSolution:public cxxNumKeyword
{

  public:
	cxxSolution();
	cxxSolution(struct solution *);
	  cxxSolution(PHREEQC_PTR_ARG_COMMA int n_user);
	  cxxSolution(PHREEQC_PTR_ARG_COMMA const std::map < int, cxxSolution > &solution_map,
				  cxxMix & mx, int n_user);
	 ~cxxSolution();

	//static cxxSolution& read(CParser& parser);

	double get_tc() const
	{
		return this->tc;
	}
	void set_tc(double tc1)
	{
		this->tc = tc1;
	}

	double get_ph() const
	{
		return this->ph;
	}
	void set_ph(double pH)
	{
		this->ph = pH;
	}

	double get_pe() const
	{
		return this->pe;
	}
	void set_pe(double pe1)
	{
		this->pe = pe1;
	}

	double get_mu() const
	{
		return this->mu;
	}
	void set_mu(double mu1)
	{
		this->mu = mu1;
	}

	double get_ah2o() const
	{
		return this->ah2o;
	}
	void set_ah2o(double ah2o1)
	{
		this->ah2o = ah2o1;
	}

	double get_total_h() const
	{
		return this->total_h;
	}
	void set_total_h(double total_h1)
	{
		this->total_h = total_h1;
	}

	double get_total_o() const
	{
		return this->total_o;
	}
	void set_total_o(double total_o1)
	{
		this->total_o = total_o1;
	}

	double get_cb() const
	{
		return this->cb;
	}
	void set_cb(double cb1)
	{
		this->cb = cb1;
	}

	double get_mass_water() const
	{
		return this->mass_water;
	}
	void set_mass_water(long double mass_water1)
	{
		this->mass_water = mass_water1;
	}

	double get_total_alkalinity() const
	{
		return this->total_alkalinity;
	}
	void set_total_alkalinity(double total_alkalinity1)
	{
		this->total_alkalinity = total_alkalinity1;
	}

	double get_total(char *string) const;
	double get_total_element(char *string) const;
	void set_total(char *string, double value);

	const cxxNameDouble & get_totals(void) const
	{
		return this->totals;
	}
	void set_totals(cxxNameDouble & nd)
	{
		this->totals = nd;
		this->totals.type = cxxNameDouble::ND_ELT_MOLES;
	}
	void clear_totals()
	{
		this->totals.clear();
	}

	const cxxNameDouble & get_master_activity(void) const
	{
		return this->master_activity;
	}
	double get_master_activity(char *string) const;
	void set_master_activity(char *string, double value);

	/*
	   double get_species_gamma(char *string)const;
	   void set_species_gamma(char *string, double value);

	   double get_isotope(char *string)const;
	   void set_isotope(char *string, double value);
	 */

	struct solution *cxxSolution2solution(PHREEQC_PTR_ARG);

	void dump_raw(std::ostream & s_oss, unsigned int indent) const;

	void read_raw(PHREEQC_PTR_ARG_COMMA CParser & parser, bool check = true);
	void multiply(double extensive);
#ifdef ORCHESTRA
	void ORCH_write(std::ostream & headings, std::ostream & input_data) const;
	void ORCH_read(std::vector < std::pair < std::string,
				   double >>output_vector,
				   std::vector < std::pair < std::string,
				   double >>::iterator & it);
	void ORCH_store_global(std::map < std::string, double >output_map);
#endif

#ifdef USE_MPI
	void mpi_pack(std::vector < int >&ints, std::vector < double >&doubles);
	void mpi_unpack(int *ints, int *ii, double *doubles, int *dd);
	void mpi_send(int task_number);
	void mpi_recv(int task_number);
#endif

  private:
	void zero();
	void add(const cxxSolution & addee, double extensive);
	// not checked
	void dump_xml(std::ostream & os, unsigned int indent = 0) const;

  protected:
	double tc;
	double ph;
	double pe;
	double mu;
	double ah2o;
	double total_h;
	double total_o;
	double cb;
	double mass_water;
	double total_alkalinity;
	cxxNameDouble totals;
	//std::list<cxxSolutionIsotope> isotopes;
	cxxNameDouble master_activity;
	cxxNameDouble species_gamma;
	cxxSolutionIsotopeList isotopes;

};

#endif // !defined(SOLUTION_H_INCLUDED)
