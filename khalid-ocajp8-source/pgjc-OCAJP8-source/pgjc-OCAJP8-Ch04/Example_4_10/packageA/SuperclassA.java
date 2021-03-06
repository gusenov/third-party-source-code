
// File: SuperclassA.java                             (1)
package packageA;

public class SuperclassA {
  public int superclassVarA;                        // (2)
  public void superclassMethodA() {/*...*/}         // (3)
}

class SubclassA extends SuperclassA {
  void subclassMethodA() { superclassVarA = 10; }   // (4) OK.
}

class AnyClassA {
  SuperclassA obj = new SuperclassA();
  void anyClassMethodA() {
    obj.superclassMethodA();                        // (5) OK.
  }
}