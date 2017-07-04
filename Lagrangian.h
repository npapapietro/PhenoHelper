#ifndef __LAGRANGIAN_CORE_H__
#define  __LAGRANGIAN_CORE_H__

#include "RootStructure.h"
#include <memory>
#include <type_traits>
#include <boost/format.hpp>

namespace Lagrangian_Form{
  using namespace Representation;


/*
* Gauge Redefinitions
*/

  struct YangMills_Groups{
    YangMills_Groups(std::string type, int N);
    YangMills_Groups(){}
    ~YangMills_Groups();
    std::shared_ptr<GroupBase> group;
    std::string TeXName;
  };

  /*
  * Particle Definitions
  */

  struct ParticleTraits {
    std::string name;
    enum {
      IsFermion = 0,
      IsScalar = 0,
      IsReal = 0,
      IsGauge = 0
    };
    boost::rational<int> spin;
    double mass;
    std::vector<std::shared_ptr<weight>> charges;
  };

  struct Fermion : public ParticleTraits
	{
		enum {
			IsFermion = 1,
		};
		boost::rational<int> spin = boost::rational<int>(1, 2);
		Fermion(std::string name, double mass);
	};

	struct Scalar : public ParticleTraits
	{
		enum {
			IsScalar = 1
		};
		boost::rational<int> spin = 0;
		Scalar(std::string name, double mass);
	};

	struct GBoson : public ParticleTraits
	{
		enum {
			IsScalar = 1,
			IsReal = 1,
			IsGauge = 1
		};
		boost::rational<int> spin = 1;
		GBoson(std::string name);
	};

/*
* Lagrangians Terms
*/
  class KineticEnergyTerm;
  class Lagrangian{
    const int dimension = 4;
    friend class KineticEnergyTerm;
    std::vector<std::shared_ptr<YangMills_Groups>> Gauge_Groups;
    std::vector<std::shared_ptr<ParticleTraits>> Particle_Contents;
  public:
    std::vector<std::shared_ptr<YangMills_Groups>> get_Gauge_Groups() const;
    std::vector<std::shared_ptr<ParticleTraits>> get_Particle_Contents() const;
  };

  class KineticEnergyTerm  {
    void Gauge_Int( Lagrangian L);
    std::string Term_To_String(int classifier, std::string _TeXName_, std::string U1charge = "");
  public:
    KineticEnergyTerm(ParticleTraits *pcle, Lagrangian L);
    std::string TeXName;
    std::shared_ptr<ParticleTraits> particle;
  };
}
#endif
