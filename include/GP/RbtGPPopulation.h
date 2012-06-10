/***********************************************************************
* $Id: //depot/dev/client3/rdock/2006.1/include/GP/RbtGPPopulation.h#3 $
* Copyright (C) Vernalis (R&D) Ltd 2006
* This file is released under the terms of the End User License Agreement
* in ../../docs/EULA.txt
***********************************************************************/

//Population class. Defines a population of CGP genomes that represent
//functions.

#ifndef _RBTGPPOPULATION_H_
#define _RBTGPPOPULATION_H_

#include "RbtGPGenome.h"
#include "RbtGPFitnessFunction.h"
#include "RbtGPFFGold.h"
#include "RbtError.h"

class RbtGPPopulation
{
public:
  static RbtString _CT;
    ///////////////////
    // Constructors
    ///////////////////
  RbtGPPopulation(RbtInt, RbtInt, RbtGPFitnessFunctionPtr, 
		          RbtReturnTypeArray&, RbtReturnTypeArray&);
	void SetTrainingSets(RbtReturnTypeArray& it, RbtReturnTypeArray sf)
	{
		ittrain = it;
		sfttrain = sf;
	}
  
    ///////////////////
    // Destructors
    ///////////////////
  RbtGPPopulation(const RbtGPPopulation &);
  virtual ~RbtGPPopulation();
  void Initialise(RbtDouble,RbtBool);
  void ScaleFitness();
  void Eval(RbtDouble,RbtBool);
  RbtGPGenomePtr Select(RbtString) const;
  
  void SelectionUpdate(RbtString);
  
  void GAstep(RbtString, RbtDouble, RbtDouble, RbtDouble, 
		      RbtDouble, RbtDouble,RbtBool) throw (RbtError);
  void EPstep(RbtString, RbtDouble, RbtDouble, RbtDouble, 
		      RbtDouble, RbtDouble,RbtBool) throw (RbtError);
  RbtGPGenomePtr Best() const;
  ostream& Print(ostream&) const;
  friend ostream& operator<<(ostream& , const RbtGPPopulation &);
  void Swap( SmartPtr<RbtGPPopulation>, RbtInt);
  void QSort(RbtGPGenomeList&);
  void QSort();
  void MergePops();
  static bool Gen_eq(RbtGPGenome*, RbtGPGenome*);
  RbtInt GetSize();
  RbtInt GetNrepl();
private:
  RbtGPGenomePtr RwSelect() const;
  RbtGPGenomePtr RkSelect() const;
  RbtGPGenomePtr TSelect(RbtDouble) const;
  RbtGPGenomeList pop;     // population: array to pointers of RbtGPGenomes
  RbtGPGenomeList newpop;  // array where the new individuals created are stored
  RbtInt popsize;         // size of population
  RbtInt nrepl;        // Number of new individuals that get 
                       // created at each generation
  RbtDouble total;     // total addition of the score values
  RbtDouble ave;       // average
  RbtDouble stdev;     // standard deviation
  RbtDouble c;         // Sigma Truncation Multiplier
  RbtDouble *psum;     // stores the partial sums of the fitness values. Used
                       // when selecting individuals from the population
  RbtRand& m_rand;     // keep a reference to the singleton 
                       // random number generator
  RbtInt bestInd;      // keeps the index of the best individual
  RbtGPFitnessFunctionPtr ff;
  RbtReturnTypeArray ittrain, sfttrain;
};
typedef SmartPtr<RbtGPPopulation> RbtGPPopulationPtr;
typedef vector<RbtGPPopulationPtr> RbtGPPopulationList;
typedef RbtGPPopulationList::iterator RbtGPPopulationListIter;

 // Compare class to compare different populations. Use to find the 
 // genome with best scoring function between all the populations
class PopCmp
{
public:
  bool operator()(const RbtGPPopulationPtr &x, const RbtGPPopulationPtr &y) const 
  {return (x->Best()->GetFitness() < y->Best()->GetFitness()); }
};


#endif  //_RbtGPPopulation_H_
 