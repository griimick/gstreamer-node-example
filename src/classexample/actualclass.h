/* cppsrc/Samples/actualclass.h */

class ActualClass {
	public:
		ActualClass(double value); //constructor
		double getValue(); //getter for the value
		double add(double toAdd); //adds the toAdd value to the value_
	private:
		double value_;
};
