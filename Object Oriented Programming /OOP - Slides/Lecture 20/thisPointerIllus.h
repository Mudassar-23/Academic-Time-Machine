  
class thisPointerClass
{
public:
    void set(int a, int b, int c);
    void print() const;

    thisPointerClass updateXYZ();
      // Postcondition: x = 2 * x; y = y + 2;
      //                z = z * z;

    thisPointerClass(int a = 0, int b = 0, int c = 0);

private:
    int x;
    int y;
    int z;
};