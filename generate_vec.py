"""
A python script to generate a c++ vector library for math
Should work with vectors with 2-9 components
2022 Matthias Quintern
"""

from os import path
#
# SETTINGS
# 
vectors = [2, 3, 4] # , 5, 6, 7, 8, 9]
letters_ = {
    2: [ "x", "y" ],
    3: [ "x", "y", "z" ],
    4: [ "x", "y", "z", "w"],
}
# \t or x-spaces
tab = "\t"
# float, double, long double
float_type = "float"
# string or None
namespace = "gz"
types = {
    "float": "f",
    "double": "d",
    "int": "i",
    "unsigned int": "u",
}
filename = "vec.hpp"
# for genstring
templateStr = "@"

#
# HELPERS
#
def classname(n):
    return "vec" + str(n)

def letters(n, i):
    if n in letters_:
        return letters_[n][i]
    else:
        return f"x{i}"


def genstring(n: int, template: str, sep=", ", offset=0):
    """
    Generate a string from a template for each vector component
    eg genstring(3, "@ + ") -> x + y + z
    """
    s = ""
    for i in range(n):
        s += template.replace(templateStr, letters(n, i + offset)) + sep
    s.removesuffix(sep)
    return s[0:len(s)-len(sep)]

def transformString(s: str, depth: int):
    """Add tabs after all but the last line break and before the first char"""
    return depth * tab + s.replace("\n", "\n" + depth * tab, s.count("\n") - 1)

def getPossiblities(i, a, depth=0):
    """
    get all possibilites to get i by addition of numbers lower than i
    eg i=3 -> 3, 2+1, 1+2, 1+1+1
    """
    if i == 0:
        return
    if i == 1:
        a.append(str(1))
        return
    for j in range(1, i):
        b = []
        # print("\t" * depth + "gp: i="+str(i)+" j="+str(j))
        getPossiblities(i-j, b, depth+1)

        for poss in b:
            # print("\t"*depth + f"{i}-{j} returned", b)
            a.append(str(j) + poss)
    a.append(str(i))



#
# GENERATORS
#
def genConstructors(n):
    constructors = []
    s = "/// Default constructor\n"
    s += classname(n) + "() : " + genstring(n, "@(0)") + " {};\n"
    constructors.append(s)

    s = "/// Create vector from scalar, all components will have value n\n"
    s += "template<typename N>\n"
    s += "(const N n) : " + genstring(n, "@(static_cast<T>(n))") + " {};\n";

    a = []
    getPossiblities(n, a)
    for possiblity in a:
        n_count = 0
        v_count = 0
        i = 0
        comment = "/// Create a " + classname(n) + " from "
        templates = "template<"
        args = classname(n) + "("
        init = " : "

        for nstr in possiblity:
            c = int(nstr)
            if c == 1:
                comment += "n "
                templates += f"typename N{n_count}, "
                args += f"N{n_count} n{n_count}, "
                init += letters(n, i) + f"(static_cast<T>(n{n_count})), "
                n_count += 1
                i += 1
            else:
                comment += f"vec{c} "
                args += "const " + classname(c) + f"<V{v_count}>& v{v_count}, "
                templates += f"typename V{v_count}, "
                for j in range(c):
                    init += letters(n, i) + "(static_cast<T>(v" + str(v_count) + "." + letters(n, j) + ")), "
                    i += 1
                v_count += 1
        templates = templates.removesuffix(", ") + ">"
        args = args.removesuffix(", ") + ")"
        init = init.removesuffix(", ") + " {};"

        s = comment + "\n" + templates + "\n" + args + init + "\n"
        constructors.append(s)

    return constructors


def genValues(n):
    s = genstring(n, "T @;\n", "")
    return s

def genAssignment(n):
    s = "/// component-wise assignment\n"
    s += "template<typename V>\n"
    s += "void operator=(const " + classname(n) + "<V>& other) {\n"
    s += genstring(n, f"\t@ = static_cast<T>(other.@);\n", "") + "};\n\n"
    s += "template<typename N>\n"
    s += "void operator=(const N& other) {\n"
    s += genstring(n, f"\t@ = static_cast<T>(other);\n", "") + "};\n\n"

    return s



def genArithmeticVectorial(n):
    operators = []
    for op in ["+", "-", "*", "/", "%"]:
        s = "/// component-wise " + op + "\n"
        s += "template<typename V>\n"
        s += classname(n) + "<T> operator" + op + "(const " + classname(n) + "<V>& other) const { return "
        s += classname(n) + "<T>(" + genstring(n, f"@ {op} static_cast<T>(other.@)") + "); };\n"
        operators.append(s)
    operators.append("\n")

    for op in ["+=", "-=", "*=", "/=", "%="]:
        s = "/// component-wise assignment" + op + "\n"
        s += "template<typename V>\n"
        s += "void operator" + op + "(const " + classname(n) + "<V>& other) {\n"
        s += genstring(n, f"\t@ {op} static_cast<T>(other.@);\n", "") + "};\n"
        operators.append(s)
    operators.append("\n")

    return operators

def genArithmeticScalar(n):
    operators = []
    for op in ["+", "-", "*", "/", "%"]:
        s = "/// component-wise " + op + "\n"
        s += "template<typename N>\n"
        s += classname(n) + "<T> operator" + op + "(const N& other) const { return "
        s += classname(n) + "<T>(" + genstring(n, f"@ {op} static_cast<T>(other.@)") + "); };\n"
        operators.append(s)
    operators.append("\n")
    for op in ["+=", "-=", "*=", "/=", "%="]:
        s = "/// component-wise assignment" + op + "\n"
        s += "template<typename N>\n"
        s += "void operator" + op + "(const N& other) {\n"
        s += genstring(n, f"\t@ {op} static_cast<T>(other.@);\n", "") + "};\n"
        operators.append(s)
    operators.append("\n")
    return operators

def genComparisonVectorial(n):
    operators = []
    for op in ["==", "<", ">"]:
        s = "/// component-wise comparison " + op + " (and)\n"
        s += "template<typename N>\n"
        s += "bool operator" + op + "(const " + classname(n) + "<N>& other) const { return "
        s += genstring(n, f"@ {op} other.@", " and ") + "; };\n"
        operators.append(s)
    operators.append("\n")
    for op, antiop in { "!=": "==", "<=": ">", ">=": "<" }.items():
        s = "/// component-wise comparison " + op + " (and)\n"
        s += "template<typename N>\n"
        s += "bool operator" + op + "(const " + classname(n) + "<N>& other) const { return "
        s += genstring(n, f"@ {antiop} other.@", " and ") + "; };\n"
        operators.append(s)
    operators.append("\n")
    return operators

def genComparisonScalar(n):
    operators = []
    for op in ["==", "<", ">"]:
        s = "/// component-wise comparison " + op + " (and)\n"
        s += "template<typename N>\n"
        s += "bool operator" + op + "(const N& other) const { return "
        s += genstring(n, f"@ {op} other.@", " and ") + "; };\n"
        operators.append(s)
    operators.append("\n")
    for op, antiop in { "!=": "==", "<=": ">", ">=": "<" }.items():
        s = "/// component-wise comparison " + op + " (and)\n"
        s += "template<typename N>\n"
        s += "bool operator" + op + "(const N& other) const { return "
        s += genstring(n, f"@ {antiop} other.@", " and ") + "; };\n"
        operators.append(s)
    return operators

def genIterator(n):
    s = """struct Iterator {
    public:
        using value_type = T;
        Iterator() : ptr(nullptr) {};
        Iterator(T* ptr) : ptr(ptr) {};
        T& operator*() { return *ptr; };
        Iterator& operator=(const Iterator& other) {
            ptr = other.ptr;
            return *this;
        };
        Iterator& operator++() { ptr += sizeof(T); return *this; };
        Iterator operator++(int) { auto copy = *this; ptr += sizeof(T); return copy; };
        friend int operator-(Iterator lhs, Iterator rhs) {
            return lhs.ptr - rhs.ptr;
        };
        bool operator==(const Iterator& other) const { return ptr == other.ptr; };
        // bool operator!=(const Iterator& other) const { return ptr != other.ptr; };
    private:
        T* ptr;
};
"""
    s += "const Iterator cbegin() const { return Iterator(&" + letters(n, 0) + "); };\n"
    s += "const Iterator cend() const { return Iterator(&" + letters(n, n-1) + "); };\n"
    s += "const Iterator begin() const { return Iterator(&" + letters(n, 0) + "); };\n"
    s += "const Iterator end() const { return Iterator(&" + letters(n, n-1) + "); };\n\n"
    return s


def genFunctional(n):
    s = "/// Returns the absolute value of the vector\n"
    s += "inline " + float_type + " abs() const { return std::sqrt(" + genstring(n, f"static_cast<{float_type}>(@ * @)", " + ") + "); };"

    if n == 2:
        s += "/// Returns x/y\n"
        s += "inline " + float_type + " ratio() const { return static_cast<" + float_type + ">(x) / y; };"
        s += "/// Returns y/x\n"
        s += "inline " + float_type + " inverseRatio() const { return static_cast<" + float_type + ">(y) / x; };"

    s += "/// Returns the min of the components\n"
    s += "inline T min() const { return std::min_element(cbegin(), cend()); };\n"

    s += "/// Returns the max of the components\n"
    s += "inline T max() const { return std::max_element(cbegin(), cend()); };\n"

    s += "/// Scalar product\n"
    s += "template<typename V>\n"
    s += "inline " + classname(n) + "<T> dot(const " + classname(n) + "<V>& other) { return " + classname(n) + "<T>("
    s += genstring(n, "@ * static_cast<T>(other.@)", " + ") + "); };\n"

    return s

def genUtility(n):
    s = "std::string to_string() const { return \"(\" + " + genstring(n, "std::to_string(@)", " + \", \" + ") + " + \")\"; };\n"

    return s

def genUsing(n):
    global types
    s = ""
    for t, c in types.items():
        s += f"using {classname(n)}{c} = {classname(n)}<{t}>;\n"
    return s

def generateFile(vectors):
    depth = 0
    s = "#pragma once\n\n#include <string>\n#include <cmath>\n#include <algorithm>\n\n"
    if namespace:
        s += "namespace " + namespace + " {\n"
        depth = 1
    for v in vectors:
        s += generateVector(v, depth)
        s += "\n"
    for v in vectors:
        s += transformString(genUsing(v), depth)
        s += "\n"
    if namespace:
        depth -= 1
        s += transformString("} // namespace " + namespace + "\n", depth)

    for i in range(1, 5):
        s = s.replace("\n" + i * tab + "\n", "\n\n")

    return s



def generateVector(n, depth):
    s = transformString("""/**
 * @brief Class containing $ numbers
 */
template<typename T>
class vec$ {
    public:
""".replace("$", str(n)), depth)

    depth += 1

    s += transformString("// Constructors\n", depth)
    for c in genConstructors(n):
        s += transformString(c, depth + 1)

    s += transformString("// Values\n", depth)
    s += transformString(genValues(n), depth + 1)

    s += transformString("// Assignment\n", depth)
    s += transformString(genAssignment(n), depth + 1)

    s += transformString("// Arithmetic\n", depth - 1)
    s += transformString("// Vectorial\n", depth)
    for o in genArithmeticVectorial(n):
        s += transformString(o, depth + 1)
    s += transformString("// Scalar\n", depth)
    for o in genArithmeticScalar(n):
        s += transformString(o, depth + 1)

    s += transformString("// Comparison\n", depth - 1)
    s += transformString("// Vectorial\n", depth)
    for o in genComparisonVectorial(n):
        s += transformString(o, depth + 1)
    s += transformString("// Scalar\n", depth)
    for o in genComparisonScalar(n):
        s += transformString(o, depth + 1)

    s += transformString("// Functional\n", depth - 1)
    s += transformString(genFunctional(n), depth + 1)

    s += transformString("// Utility\n", depth - 1)
    s += transformString(genUtility(n), depth + 1)
    s += transformString(genIterator(n), depth + 1)

    s += transformString("}; // vec" + str(n) + "\n", depth - 1)

    return s


def write_file(s):
    global filename
    if path.exists(filename):
        answer = input("File " + filename + "already exists. Overwrite? (y/n): ")
        if answer not in "yY":
            return

    with open(filename, "w") as file:
        file.write(s)

if __name__ == "__main__":
    write_file(generateFile(vectors))



