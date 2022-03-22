#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <cassert>

struct Result {  //struct ti dice come funziona, ma poi gli puoi dare coefficienti diversi che si comporteranno secondo quel modo...Result è un nome inventato
  double A{};  // le graffe servono perchè stai dichiarando qualcosa. Scrivere A{} e A=0 è uguale
  double B= 0;
};

class Regression {
 private:
  int N_{};          // oppure int N_=0. Significa la stessa cosa
  double sium_x_{};  // le chiami come vuoi perchè sono delle variabili
  double sium_y_{};
  double sium_x2_ = 0;
  double sium_xy_ = 0;

 public:
  void add(double x, double y)  // ogni volta che chiamo add aggiunge una coppia
                                // di valori e ci fa delle operazioni
  {
    ++N_;
    sium_x_ += x;
    sium_y_ += y;
    sium_x2_ += x * x;
    sium_xy_ += x * y;
  }
  Result fit() const  // come add, ogni volta che la chiami fa qualcosa, e anche qui
                // il nome è inventato //const perchè con fit non stai cambiando nulla alle variabili private
  {

      assert(sium_x_!= 0 && N_>1 ); // x=0 gli da il valore, x==0 controlla se il valore è uguale //dentro l'assert ci metti la cosa che se non è soddisfatta muore
    double Q = (sium_y_ * sium_x2_ - sium_x_ * sium_xy_) /
               (N_ * sium_x2_ - sium_x_ * sium_x_);
    double M = (N_ * sium_xy_ - sium_x_ * sium_y_) /
               (N_ * sium_x2_ - sium_x_ * sium_x_);
     Result ciao{Q,M};       
    return ciao;
  }
};

TEST_CASE("Testing Regression") {
  Regression
      reg;  // es. Regression Valerio, così la chiami (inizializzi la classe)
            // Valerio e ogni volta che la chiami fai Valerio.add o Valerio.fit
    //è qua che gli di i dati, non più in ccin
  reg.add(1., 3.);
  reg.add(1., 3.);

  auto result = reg.fit();
  CHECK(result.A == doctest::Approx(1.));
  CHECK(result.B == doctest::Approx(1.));
}