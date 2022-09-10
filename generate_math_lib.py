#!/bin/python3
"""
A python script to generate a c++ vector and matrix library for mathematics.
Should work with vectors/matrix up to a length of 9.

The script generates a header (and source) for each container (vector/matrix).
There are overloads for each container which allow convenient usage. 
Eg multiplication with matrix rules is as easy as: (example)
mat3x2 = mat3x3 * mat3x2
n = rvec4 * vec4
To be accurate, there is a differentiation between row and column vector, they are basically the same but each has a separate class which differ only for the matrix multiplication overloads.

To help compile times, the templated definitions of most methods is in the source file (by default).
That means that all templates must be explictly instantiated beforehand. The instantiations are in the tpp file included by the cpp files.
Specify the needed types by adding them to templateInstantiationIntTypes and templateInstantiationFloatTypes respectively (the differentiation is needed for the modulo operator).

All that makes the generated library is not memory efficient, but very fast and convenient.

AS OF NOW, THIS SOFTWARE IS NEARLY UNTESTED AND BOUND TO CONTAIN LOTS OF BUGS.

Copyright  ©  2022  Matthias  Quintern.
This software comes with no warranty.
This software is licensed under the GPL3
"""

from os import path, mkdir
#
# SETTINGS
# 
# generate up to MAX_N (-> vecN, matNxN)
MAX_N = 4
letters_ = {
    2: [ "x", "y" ],
    3: [ "x", "y", "z" ],
    4: [ "x", "y", "z", "w"],
}
directory = "math"
#
# \t or x-spaces
tab = "\t"
# float, double, long double...
float_type = "float"
# string or None
namespace = "gz"
typeShorts = {
    "float": "f",
    "double": "d",
    "int": "i",
    "unsigned int": "u",
}
include_static_asserts = True
include_template_instantiations = True
templateInstantiationIntTypes = [  # these must be usable with %
    # "uint8_t"
    "uint8_t", "uint16_t", "uint32_t", "uint64_t",
    "int8_t", "int16_t", "int32_t", "int64_t",
]
templateInstantiationFloatTypes = [
    # "float",
    "float", "double", "long double"
]
templateInstantiationTypes = templateInstantiationFloatTypes + templateInstantiationIntTypes


headerIncludes = [ "\"concepts.hpp\"", "\"../container/iterator.hpp\"" ]
sourceIncludes = ["<cmath>", "<algorithm>", "<cstdint>"]


# shorthands
Number_N = ("Number", "N")
Class_T = [("Number", "T")]
constexpr = "constexpr"
inline = "inline"


def template(t:list[tuple[str, str]]):
    if len(t) == 0:
        return ""
    s = "template<"
    for temp in t:
        s += temp[0] + " " + temp[1] + ", "
    return s.removesuffix(", ") + ">\n"


class Member:
    def __init__(self, class_:str, name:str, c_temp:list=[], m_temp:list=[], prefixes:list=[], ret_type:str="", args:str="", init:str="", const=False, body:list=[], comment:str=""):
        """
        :param class: class name
        :param name: member name
        :param c_temp: list of templates of the class
        :param m_temp: list of templates of the member
        :param prefixes:  things like constexpr, inline...
        :param ret_type: return type of the member
        :param args: arguments of the member
        :param init: initializion of the member
        :param const: True if the method does not change the object
        :param body: method body
        :param comment: a single-line docstring

        template<c_temp>
        class class {
            comment
            template<m_temp>
            prefixes ret_type name(args) const : init {
                body
            }
        }
        """
        self.class_ = class_
        self.name = name
        self.prefixes = prefixes
        self.c_temp = c_temp
        self.m_temp = m_temp
        self.ret_type = ""
        if ret_type: self.ret_type = ret_type + " "
        self.args = args
        self.init = ""
        if init: self.init = f"\n{tab} : {init} "
        self.const = ""
        if const: self.const = " const"
        self.body = body
        self.comment = ""
        if comment: self.comment = "/// " + comment + "\n"

    def getArgsAsList(self):
        args = []
        const = False
        arglist = self.args.split(", ")
        for i in range(len(arglist)):
            if "const" in arglist[i]:
                arglist[i] = arglist[i].replace("const ", "")
                const = True
            args.append(arglist[i].split(" "))
            if const:
                args[-1][0] = "const " + args[-1][0]
        return args

    def defintionH(self, depth:int=0):
        """
        Return the defition to be used in a header
        """
        s = ""
        s += self.comment
        s += template(self.m_temp)
        for p in self.prefixes:
            s += p + " "
        s += self.ret_type + self.name + f"({self.args}){self.const};\n"
        return transformString(s, depth)

    def source(self, depth:int=0):
        """
        Return the defition + declarations for a source file
        """
        s = ""
        class_ = self.class_
        s += template(self.c_temp)
        if len(self.c_temp) > 0:
            class_ = self.class_ + "<"
            for t in self.c_temp:
                class_ += f"{t[1]}, "
            class_ = class_.removesuffix(", ") + ">"

        s += template(self.m_temp)
        for p in self.prefixes:
            s += p + " "
        s += f"{self.ret_type}{class_}::{self.name}({self.args}){self.const}{self.init}"
        if self.body:
            s += " {\n"
            body = ""
            for l in self.body: body += l + "\n"
            s += transformString(body, depth)
            s += "}\n"
        else:
            s += "{}"
        return transformString(s, depth)

    def header(self, depth:int=0):
        """
        Return the defition + declarations for a header file
        """
        s = ""
        s += self.comment
        s += template(self.m_temp)
        for p in self.prefixes:
            s += p + " "
        s += f"{self.ret_type}{self.name}({self.args}){self.const}{self.init}"
        if self.body:
            s += " {\n"
            body = ""
            for l in self.body: body += l + "\n"
            s += transformString(body, depth+1)
            s += "}\n"
        else:
            s += "{}\n"
        return transformString(s, depth)

    def isConstructor(self):
        return self.class_ == self.name

    def templateInstantiations(self):
        """
        generate instantiations for all templates
        right now only works with Number concepts
        temp<Number T>
        temp<Number N>
        void Class<T>::operator+(class<N>) {
        ->
        temp<> void Class<float>::operator+(class<float>)
        ...
        """
        if len(self.m_temp) == 0:
            return ""
        class_ = self.class_
        if len(self.c_temp) > 0:
            class_ = self.class_ + "<"
            for t in self.c_temp:
                class_ += f"{t[1]}, "
            class_ = class_.removesuffix(", ") + ">"

        arglist = self.getArgsAsList()
        args = ""
        for arg in arglist:
            args += arg[0] + ", "
        args = args.removesuffix(", ")
        name = self.name.removesuffix(" ")
        if len(self.m_temp) > 0:
            name += " <"
            for type_ in self.m_temp:
                name += type_[1] + ", "
            name = name.removesuffix(", ") + ">"

        method = f"{self.ret_type}{class_}::{name}({args}){self.const}"
        instantiations = []
        if len(self.c_temp) > 0 or len(self.m_temp) > 0:
            if "%" in method: types = templateInstantiationIntTypes
            else: types = templateInstantiationTypes
            getTemplateInsts(method, instantiations, self.c_temp + self.m_temp, types, 0)
        s = ""
        for spec in instantiations:
            s += spec + "\n"
        return s + "\n";


#
# HELPERS
#
def classname(row, col, template=""):
    name = ""
    if template and col == 1 and row == 1:
        return template
    elif col == 1:
        name =  "vec" + str(row)
    elif row == 1:
        name = "rvec" + str(col)
    else:
        name = "mat" + str(row) + "x" + str(col);
    if template:
        name += "<" + template + ">"
    return name


def concept(row, col, template=""):
    name = ""
    if template and col == 1 and row == 1:
        return template
    elif col == 1:
        name =  "ColumnVector" + str(row)
    elif row == 1:
        name = "RowVector" + str(col)
    else:
        name = "Mat" + str(row) + "x" + str(col);
    if template:
        name += "<" + template + ">"
    return name


def classnameFromConcept(concept:str):
    name = ""
    number = ""
    if concept.startswith("ColumnVector"):
        name = "vec"
        number = concept.removeprefix("ColumnVector")
    elif concept.startswith("RowVector"):
        name = "rvec"
        number = concept.removeprefix("RowVector")
    elif concept.startswith("Mat"):
        name = "mat"
        number = concept.removeprefix("Mat")
    return name + number


def varname(r, c, rows, cols):
    """Get the name of the variable in row r and column c"""
    if rows == 1:
        if cols in letters_.keys():
            return letters_[cols][c]
        else:
            return f"x{r+1}"
    elif cols == 1:
        if rows in letters_.keys():
            return letters_[rows][r]
        else:
            return f"x{c+1}"
    else:
        return f"x{r+1}_{c+1}"


def varnameI(i, rows, cols):
    """Get the name of the ith variable"""
    if rows == 1:
        if cols in letters_.keys():
            return letters_[cols][i%cols]
        else:
            return f"x{i+1}"
    elif cols == 1:
        if rows in letters_.keys():
            return letters_[rows][i%rows]
        else:
            return f"x{i+1}"
    else:
        return f"x{i%rows+1}_{i%cols+1}"



def genstring(row: int, col: int, template: str, sep=", "):
    """
    Generate a string from a template for each vector component
    eg genstring(3, "@ + ") -> x + y + z
    @C -> varname(1, c, 1, col)
    @R -> varname(r, 1, row, 1)
    @ -> varname(r, c, row, col)
    @c -> c
    @r -> r

    """
    s = ""
    for r in range(row):
        for c in range(col):
            s += template.replace("@r", str(r)).replace("@c", str(c)).replace("@R", varname(r, c, row, 1)).replace("@C", varname(r, c, 1, col)).replace("@", varname(r, c, row, col)) + sep

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
def genConstructors(row, col):
    constructors = []
    class_ = classname(row, col)

    # default
    constructors.append(Member(class_, class_, c_temp=Class_T, prefixes=[constexpr], init=genstring(row, col, "@(0)"), comment="Default constructor"))

    # from single scalar
    constructors.append(Member(class_, class_, c_temp=Class_T, prefixes=[constexpr], m_temp=[["Number", "N"]], args="const N n", init=genstring(row, col, "@(static_cast<T>(n))"), comment="Create from scalar, all components will have value n"))

    # generate a constructor for every possible vector initialization
    if row == 1 or col == 1:
        rows_or_cols = max(row, col)  # vec and rvec share same variable names
        size = max(row, col)
        a = []
        getPossiblities(size, a)
        for possiblity in a:
            n_count = 1  # counts how many numbers appear 
            v_count = 1  # counts how many vectors appear
            i = 0  # index the member variable to initialize
            comment = "Create from "
            templates = []
            args = ""
            init = ""

            for nstr in possiblity:
                n = int(nstr)
                if n == 1:  # if number
                    comment += "n "
                    templates.append(("Number", f"N{n_count}"))
                    args += f"N{n_count} n{n_count}, "
                    init += varnameI(i, row, col) + f"(static_cast<T>(n{n_count})), "
                    n_count += 1
                    i += 1
                else:  # if vector
                    comment += f"vec{n} "
                    args += f"const V{v_count}& v{v_count}, "
                    templates.append((f"Vector{rows_or_cols}", f"V{v_count}"))
                    for j in range(n):
                        init += varnameI(i, rows_or_cols, 1) + "(static_cast<T>(v" + str(v_count) + "." + varnameI(j, rows_or_cols, 1) + ")), "
                        i += 1
                    v_count += 1
            args = args.removesuffix(", ")
            init = init.removesuffix(", ")
            constructors.append(Member(class_, class_, c_temp=Class_T, m_temp=templates, prefixes=[constexpr], args=args, init=init, comment=comment))
    # constructor for all matrices
    else:
        # from scalar
        constructors.append(Member(class_, class_, c_temp=Class_T, m_temp=[ t.split(" ") for t in genstring(row, col, f"Number N@r_@c").split(", ")], prefixes=[constexpr],
                                   args=genstring(row, col, "const N@r_@c @"), init=genstring(row, col, "@(static_cast<T>(@))"), comment="Create from scalars"))

        # from row vec
        constructors.append(Member(class_, class_, c_temp=Class_T, m_temp=[ t.split(" ") for t in genstring(row, 1, f"RowVector{col} V@r").split(", ")], prefixes=[constexpr],
                                   args=genstring(row, 1, "const V@r& v@r"), init=genstring(row, col, "@(static_cast<T>(v@r.@C))"), comment="Create from row vectors"))

        # from col vec
        constructors.append(Member(class_, class_, c_temp=Class_T, m_temp=[ t. split(" ") for t in genstring(1, col, f"ColumnVector{row} V@c").split(", ")], prefixes=[constexpr],
                                   args=genstring(1, col, "const V@c& v@c"), init=genstring(row, col, "@(static_cast<T>(v@c.@R))"), comment="Create from column vectors"))

    return constructors


def genValues(row, col):
    s = genstring(row, col, "T @;\n", "")
    return s

def genAssignment(row, col):
    # TODO opt idea: memcpy for component wise assignment when types have same size
    members = []
    members.append(Member(classname(row, col), "operator=", c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr], ret_type="void",
                          args=f"const {classname(row, col, 'N')}& other", body=genstring(row, col, f"\t@ = static_cast<T>(other.@);\n", "").split("\n"), comment="Component-wise assignment"))

    members.append(Member(classname(row, col), "operator=", c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr], ret_type="void",
                          args="const N& other", body=genstring(row, col, f"\t@ = static_cast<T>(other);\n", "").split("\n"), comment="Assignment from scalar"))

    return members



ops = {
    "+": "operator+",
    "-": "operator-",
    "%": "operator%",
    "*": "compWiseMult",
    "/": "compWiseDiv",
}
as_ops = {
    "+=": "operator+=",
    "-=": "operator-=",
    "%=": "operator%=",
    "*=": "compWiseAssMult",
    "/=": "compWiseAssDiv",
}
def genArithmeticVectorial(row, col):
    operators = []
    for op, opname in ops.items():
        body = "return " + classname(row, col, "T") + "(" + genstring(row, col, f"@ {op} static_cast<T>(other.@)") + ");"
        operators.append(Member(classname(row, col), opname, c_temp=Class_T, m_temp=[(concept(row, col), concept(row, col)[0])], prefixes=[constexpr], ret_type=classname(row, col, "T"),
                                args=f"const {concept(row, col)[0]}& other", const=True, body=[body], comment=f"Component-wise {op}"))

    for op, opname in as_ops.items():
        body = genstring(row, col, f"\t@ {op} static_cast<T>(other.@);", "\n")
        operators.append(Member(classname(row, col), opname, c_temp=Class_T, m_temp=[(concept(row, col), concept(row, col)[0])], prefixes=[constexpr], ret_type="void",
                                args=f"const {concept(row, col)[0]}& other", body=body.split("\n"), comment=f"Component-wise assignment {op}"))
    return operators

def genArithmeticScalar(row, col):
    operators = []
    for op, opname in ops.items():
        body = "return " + classname(row, col, "T") + "(" + genstring(row, col, f"@ {op} static_cast<T>(other)") + ");"
        operators.append(Member(classname(row, col), opname, c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr], ret_type=classname(row, col, "T"),
                                args=f"const N& other", const=True, body=[body], comment=f"Component-wise {op} with scalar"))
    for op, opname in as_ops.items():
        body = genstring(row, col, f"\t@ {op} static_cast<T>(other);", "\n")
        operators.append(Member(classname(row, col), opname, c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr], ret_type="void",
                                args=f"const N& other", body=body.split("\n"), comment=f"Component-wise assignment {op} from scalar"))
    return operators


def genComparisonVectorial(row, col):
    operators = []
    for op in ["==", "<", ">"]:
        body = "return " + genstring(row, col, f"@ {op} other.@", " and ") + ";"
        operators.append(Member(classname(row, col), f"operator{op}", c_temp=Class_T, m_temp=[(concept(row, col), concept(row, col)[0])], prefixes=[constexpr], ret_type="bool",
                                args=f"const {concept(row, col)[0]}& other", const=True, body=[body], comment=f"Component-wise comparison {op} (and)"))
    for op, antiop in { "!=": "==", "<=": ">", ">=": "<" }.items():
        body = "return " + genstring(row, col, f"@ {antiop} other.@", " and ") + ";"
        operators.append(Member(classname(row, col), f"operator{op}", c_temp=Class_T, m_temp=[(concept(row, col), concept(row, col)[0])], prefixes=[constexpr], ret_type="bool",
                                args=f"const {concept(row, col)[0]}& other", const=True, body=[body], comment=f"Component-wise comparison {op} (and)"))
    return operators

def genComparisonScalar(row, col):
    operators = []
    for op in ["==", "<", ">"]:
        body = "return " + genstring(row, col, f"@ {op} other", " and ") + ";"
        operators.append(Member(classname(row, col), f"operator{op}", c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr], ret_type="bool",
                                args=f"const N& other", const=True, body=[body], comment=f"Component-wise comparison {op} (and)"))
    for op, antiop in { "!=": "==", "<=": ">", ">=": "<" }.items():
        body = "return " + genstring(row, col, f"@ {antiop} other", " and ") + ";"
        operators.append(Member(classname(row, col), f"operator{op}", c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr], ret_type="bool",
                                args=f"const N& other", const=True, body=[body], comment=f"Component-wise comparison {op} (and)"))
    return operators



def getDependecyClasses(row, col):
    """
    Get all class names that row,col class depends on for matrix multplication and the .row() and .column() methods
    The dependencies will be forward declared in the header and included in the source
    """
    deps = []
    # for .row(), .column()
    if row > 1 and col > 1:
        deps.append(classname(row, 1))
        deps.append(classname(1, col))

    # for matrix mult
    for i in range(1, MAX_N + 1):
        # results from matrix calculations
        deps.append(classname(row, i))

        # operands from matrix calculations
        deps.append(classname(col, i))

    deps = list(dict.fromkeys(deps))
    # remove vec1
    if classname(1, 1) in deps:
        deps.remove(classname(1, 1))
    if classname(row, col) in deps:
        deps.remove(classname(row, col))
    deps.sort()
    return deps


def genArithmeticMatrix(row, col):
    """
    Generate all matrix multiplications.
    dimensions of result = mat(row, other.col) where col = other.row
    """
    operators = []
    other_row = col
    other_cols = [ i for i in range(1, MAX_N + 1) ]
    for other_col in other_cols:
        if (row == 1 and other_col == 1) or (other_row == 1 and other_col == 1):  # if ret_type or arg is a scalar
            continue
        body = classname(row, other_col, "T") + " new_;\n"
        for r in range(row):
            for o_c in range(other_col):
                body += "new_." + varname(r, o_c, row, other_col) + " = "
                for i in range(col):
                    # print(f"genArithmeticMatrix: {row}x{col} * {other_row}x{other_col}", r, o_c, "->", c)
                    body += varname(r, i, row, col) + " * other." + varname(i, o_c, other_row, other_col) + " + "
                body = body.removesuffix(" + ") + ";\n"
        # if scalar, put ret_type creation and assignment in same line
        body = body.replace("new_;\nnew_." + varname(0, 0, 1, 1) + " =", "new_ =") + "return new_;"
        arg_concept = concept(other_row, other_col)
        operators.append(Member(classname(row, col), "operator*", c_temp=Class_T, m_temp=[(arg_concept, arg_concept[0])], prefixes=[constexpr], ret_type=classname(row, other_col, "T"), const=True,
                                args=f"const {arg_concept[0]}& other", body=body.split("\n"), comment=f"Matrix multiplication with {classname(other_row, other_col)} -> {classname(row, other_col)}"))

    return operators


def genSubscription(row, col):
    operators = []
    # [i]
    operators.append(Member(classname(row, col), "operator[]", c_temp=Class_T, prefixes=[constexpr], ret_type="T",
                            args="std::size_t i", const=True, body=[f"return *(&{varname(0, 0, row, col)} + sizeof(T) * i);"], comment="Get the ith element. i starts at 0"))

    if row > 1 and col > 1:
        # at(row, col)
        body = f"return *(&{varname(0, 0, row, col)} + (row * {row} + col * {col}) * sizeof(T));"
        operators.append(Member(classname(row, col), "at", c_temp=Class_T, prefixes=[constexpr], ret_type="T",
                                args="std::size_t row, std::size_t col", const=True, body=[body], comment="Get the element at row and col. row and col start at 0"))

        # row()
        body = f"return {classname(1, col, 'T')}(" + genstring(1, col, f"*(&{varname(0, 0, row, col)} + ({row} * @c + i) * sizeof(T))") + ");"
        operators.append(Member(classname(row, col), "row", c_temp=Class_T, prefixes=[constexpr], ret_type=classname(1, col, 'T'),
                                args="std::size_t i", const=True, body=[body], comment="Get the ith row as column vector. i starts at 0"))

        # column()
        body = f"return {classname(row, 1, 'T')}(" + genstring(row, 1, f"*(&{varname(0, 0, row, col)} + ({col} * @r + i) * sizeof(T))") + ");"
        operators.append(Member(classname(row, col), "column", c_temp=Class_T, prefixes=[constexpr], ret_type=classname(row, 1, 'T'),
                                args="std::size_t i", const=True, body=[body], comment="Get the ith column as row vector. i starts at 0"))

    return operators


def genIterator(row, col):
    members = []
    its = [
        ("cbegin", "return Iterator(const_cast<T*>(&" + varname(0, 0, row, col) + "));", "Return an Iterator to the first element"),
        ("cend", "return Iterator(const_cast<T*>(&" + varname(row-1, col-1, row, col) + " + sizeof(T)));", "Return an Iterator past the last element"),
        ("begin", "return Iterator(const_cast<T*>(&" + varname(0, 0, row, col) + "));", "Return an Iterator to the first element"),
        ("end", "return Iterator(const_cast<T*>(&" + varname(row-1, col-1, row, col) + " + sizeof(T)));", "Return an Iterator past the last element"),
    ]
    for name, body, comment in its:
        members.append(Member(classname(row, col), name, c_temp=Class_T, prefixes=[constexpr], ret_type="Iterator<T>", const=True, body=[body], comment=comment))
    return members


def genFunctional(row, col):
    members = []
    # abs
    members.append(Member(classname(row, col), "abs", c_temp=Class_T, prefixes=[constexpr, inline], ret_type=float_type,
                          const=True, body=["return std::sqrt(" + genstring(row, col, f"static_cast<{float_type}>(@ * @)", " + ") + ");"], comment="Returns the absolute value of the vector (sqrt of scalar product with itself)"))

    if (row == 2 and col == 1) or (col == 2 and row == 1):
        # ratio
        members.append(Member(classname(row, col), "ratio", c_temp=Class_T, prefixes=[constexpr, inline], ret_type=float_type,
                              const=True, body=["return static_cast<" + float_type + f">({varnameI(0, row, col)}) / {varnameI(1, row, col)};"], comment=f"Returns x/y"))

        # inverse ratio
        members.append(Member(classname(row, col), "invereseRatio", c_temp=Class_T, prefixes=[constexpr, inline], ret_type=float_type,
                              const=True, body=["return static_cast<" + float_type + f">({varnameI(1, row, col)}) / {varnameI(0, row, col)};"], comment=f"Returns y/x"))


    # min
    members.append(Member(classname(row, col), "min", c_temp=Class_T, prefixes=[constexpr, inline], ret_type="T", const=True,
                          body=["return *std::min_element(cbegin(), cend());"], comment="Returns the min of the components"))

    # max
    members.append(Member(classname(row, col), "max", c_temp=Class_T, prefixes=[constexpr, inline], ret_type="T", const=True,
                          body=["return *std::max_element(cbegin(), cend());"], comment="Returns the max of the components"))

    # dot
    body = f"return " + genstring(row, col, "@ * static_cast<T>(other.@)", " + ") + ";"
    members.append(Member(classname(row, col), "dot", c_temp=Class_T, m_temp=[Number_N], prefixes=[constexpr, inline], ret_type="T", const=True,
                          args=f"const {classname(row, col, 'N')}& other", body=[body], comment="Scalar product (x1 * other.x1 +  x2 * other.x2 ...)"))
    return members


def genUtility(row, col):
    s = "\n"
    # s = "std::string to_string() const { return \"(\" + " + genstring(row, col, "std::to_string(@)", " + \", \" + ") + " + \")\"; };\n"
    return s


def genUsing(row, col):
    global typeShorts
    s = ""
    for t, c in typeShorts.items():
        s += f"using {classname(row, col)}{c} = {classname(row, col)}<{t}>;\n"
    return s



#
# TEMPLATE INSTANTIATION
#
def getTemplateInsts(method_name, instantiations, templates, types, depth=0):
    """ method name must be like this:
    constexpr ret_type Class<T>::name<U>(int, U) const;"""
    if depth < len(templates):
        if templates[depth][0] == "Number":
            for n in types:
                newmethod = method_name.replace(
                    f"<{templates[depth][1]}>", f"<{n}>").replace(
                    f"{templates[depth][1]} ", f"{n} ").replace(
                    f"{templates[depth][1]})", f"{n})").replace(
                    f"{templates[depth][1]},", f"{n},").replace(
                    f"{templates[depth][1]}& ", f"{n}& ").replace(
                    f"{templates[depth][1]}&)", f"{n}&)").replace(
                    f"{templates[depth][1]}&,", f"{n}&,")
                getTemplateInsts(newmethod, instantiations, templates, types, depth+1)
        else:
            for n in types:
                newmethod = method_name.replace(
                    f"<{templates[depth][1]}>", f"<{classnameFromConcept(templates[depth][0])}<{n}>>").replace(
                    f"{templates[depth][1]} ", f"{classnameFromConcept(templates[depth][0])}<{n}> ").replace(
                    f"{templates[depth][1]})", f"{classnameFromConcept(templates[depth][0])}<{n}> ").replace(
                    f"{templates[depth][1]},", f"{classnameFromConcept(templates[depth][0])}<{n}> ").replace(
                    f"{templates[depth][1]}& ", f"{classnameFromConcept(templates[depth][0])}<{n}>& ").replace(
                    f"{templates[depth][1]}&)", f"{classnameFromConcept(templates[depth][0])}<{n}>&)").replace(
                    f"{templates[depth][1]}&,", f"{classnameFromConcept(templates[depth][0])}<{n}>&,")
                getTemplateInsts(newmethod, instantiations, templates, types, depth+1)
    elif depth == len(templates) and len(templates)> 0:
        instantiations.append("template " + method_name + ";")


#
# GENERATION
#
def generateFiles(row, col):
    hd = 0  # header depth
    sd = 0  # source and template depth

    # header
    h = "#pragma once\n\n"
    # source
    s = "#include \"" + classname(row, col) + ".hpp\"\n\n"
    # template instantiations
    t = f"// template instantiations for {classname(row, col)}\n\n"

    dependencies = getDependecyClasses(row, col)
    for dep in dependencies:
        s += "#include \"" + dep + ".hpp\"\n"
    s += "\n"
    for i in headerIncludes:
        h += "#include " + i + "\n"
    h += "\n"
    for i in sourceIncludes:
        s += "#include " + i + "\n"
    s += "\n"
    if namespace:
        h += "namespace " + namespace + " {\n\n"
        s += "namespace " + namespace + " {\n\n"
        t += "namespace " + namespace + " {\n\n"
        hd += 1
        sd += 1

    # template instantiations
    if include_template_instantiations:
        for typ in templateInstantiationTypes:
            t += transformString("template class " + classname(row, col, typ) + ";\n", 0)
            t += "\n"

    # forward declarations
    h += transformString("// Forward declarations\n", hd)
    for dep in dependencies:
        h += transformString("template<Number T>\nclass " + dep + ";\n", hd)
    h += "\n"

    header, source, templates = generateMatrix(row, col, hd, sd)
    h += header + "\n"
    s += source + "\n"
    t += templates + "\n"

    if include_static_asserts:
        h += transformString("static_assert(" + concept(row, col, classname(row, col, "int")) +", \"" + classname(row, col, "int") + " does not satisfy the concept " + concept(row, col) + "\");\n", hd)

    if namespace:
        hd -= 1
        sd -= 1
        h += transformString("} // namespace " + namespace + "\n", hd)
        s += transformString("} // namespace " + namespace + "\n", hd)
        t += transformString("} // namespace " + namespace + "\n", hd)

    for i in range(1, 5):
        h = h.replace("\n" + i * tab + "\n", "\n\n")
        s = s.replace("\n" + i * tab + "\n", "\n\n")

    return h, s, t


def append(header:str, source:str, templates:str, members:list[Member], hdepth:int, sdepth:int):
    for m in members:
        split = True
        if m.isConstructor() or (len(m.body) < 2 and len(m.m_temp) > 1):
            split = False

        if split:
            header += m.defintionH(hdepth)
            source += m.source(sdepth)
            templates += m.templateInstantiations()
        else:
            header += m.header(hdepth)
    return header, source, templates




def generateMatrix(r, c, hd, sd):
    h = transformString(
"""/**
 * @brief Class containing $ numbers
 */
 """.replace("$", str(r*c)), hd)
    h += transformString("""template<Number T>
class $ {
    public:
""".replace("$", classname(r, c)), hd)

    s = transformString("""//
// CLASS $
//
""".replace("$", classname(r, c)), sd)


    t = ""

    hd += 1  # header depth
    # sd += 1  # source depth

    if classname(r, c).startswith("vec"):
        h += transformString("/// just to satisfy concept ColumnVector\nusing isColumnVector = T;\n", hd + 1)
    elif classname(r, c).startswith("rvec"):
        h += transformString("/// just to satisfy concept RowVector\nusing isRowVector = T;\n", hd + 1)

    h += transformString("// Constructors\n", hd)
    h, s, t = append(h, s, t, genConstructors(r, c), hd+1, sd)

    h += transformString("// Values\n", hd)
    h += transformString(genValues(r, c), hd+1)

    h += transformString("// Assignment\n", hd)
    h, s, t = append(h, s, t, genAssignment(r, c), hd+1, sd)

    h += transformString("// Arithmetic\n", hd-1)
    h += transformString("// Vectorial\n", hd)
    h, s, t = append(h, s, t, genArithmeticVectorial(r, c), hd+1, sd)
    h += transformString("// Scalar\n", hd)
    h, s, t = append(h, s, t, genArithmeticScalar(r, c),hd+1, sd)
    h += transformString("// Matrix Multiplication\n", hd)
    h, s, t = append(h, s, t, genArithmeticMatrix(r, c), hd+1, sd)

    h += transformString("// Comparison\n", hd-1)
    h += transformString("// Vectorial\n", hd)
    h, s, t = append(h, s, t, genComparisonVectorial(r, c),hd+1, sd)
    h += transformString("// Scalar\n", hd)
    h, s, t = append(h, s, t, genComparisonScalar(r, c), hd+1, sd)


    h += transformString("// Functional\n", hd - 1)
    h, s, t = append(h, s, t, genFunctional(r, c), hd+1, sd)

    h += transformString("// Utility\n", hd-1)
    h, s, t = append(h, s, t, genSubscription(r, c), hd+1, sd)
    h, s, t = append(h, s, t, genIterator(r, c), hd + 1, sd)

    h += transformString("}; // " + classname(r, c) + "\n\n", hd - 1)
    h += transformString(genUsing(r, c), hd - 1)
    h += "\n"
    s += "\n"
    t += "\n"

    return h, s, t


#
# CONCEPTS
#
def generateConceptsFile(row, col):
    # Number
    s = "#pragma once\n\n"
    s += "#include <concepts>\n\n"
    s += "// Number\n"
    s += "template<typename T>\n"
    s += "concept Number = std::integral<T> or std::floating_point<T>;\n\n"

    s += "// VectorX\n"
    for i in range(2, max(row, col)):
        s += "template<typename T>\n"
        # s += "concept Vector" + str(i) + " = requires(T t) { " + genstring(i, 1, "{ t.@ } -> Number; ", "") + "};\n\n"
        s += "concept Vector" + str(i) + " = requires(T t) {\n" + genstring(i, 1, tab + "requires Number<decltype(t.@)>;\n", "") + "} and requires(T t) { sizeof(t." + varname(0, 0, i, 1) + ") == (sizeof(T) * " + str(i) + "); };\n\n"
    s += "// RowVectorX\n"
    for i in range(2, max(row, col)):
        s += "template<typename T>\n"
        s += "concept RowVector" + str(i) + " = Vector" + str(i) + "<T> and Number<typename T::isRowVector>;\n\n"
    s += "// ColumnVectorX\n"
    for i in range(2, max(row, col)):
        s += "template<typename T>\n"
        s += "concept ColumnVector" + str(i) + " = Vector" + str(i) + "<T> and Number<typename T::isColumnVector>;\n\n"
    s += "// Matrices\n"
    for r in range(2, row):
        for c in range(2, col):
            s += "template<typename T>\n"
            # s += "concept " + concept(r, c) + " = requires(T t) { t -> template " + classname(r, c) + "; };\n"
            s += "concept " + concept(r, c) + " = requires(T t) {\n" + genstring(r, c, tab + "requires Number<decltype(t.@)>;\n", "") + "};\n" # and requires(T t) { sizeof(t." + varname(0, 0, r, c) + ") == (sizeof(T) * " + str(r*c) + "); };\n\n"
    return s


##
## ITERATORS
##
#def generateIteratorFile():
#    i = "#pragma once\n"
#    if namespace:
#        i += f"namespace {namespace} " + "{\n"

#    i += """

#template<typename T>
#struct Iterator {
#    public:
#        using value_type = T;
#        Iterator() : ptr(nullptr) {};
#        Iterator(T* ptr) : ptr(ptr) {};
#        T& operator*() const { return *ptr; };
#        Iterator& operator=(const Iterator& other) {
#            ptr = other.ptr;
#            return *this;
#        };
#        Iterator& operator++() { ptr += sizeof(T); return *this; };
#        Iterator operator++(int) { auto copy = *this; ptr += sizeof(T); return copy; };
#        friend int operator-(Iterator lhs, Iterator rhs) {
#            return lhs.ptr - rhs.ptr;
#        };
#        bool operator==(const Iterator& other) const { return ptr == other.ptr; };
#        // bool operator!=(const Iterator& other) const { return ptr != other.ptr; };
#    private:
#        T* ptr;
#}; // Iterator
#"""

#    if include_static_asserts:
#        i += 'static_assert(std::forward_iterator<Iterator<int>>, "Iterator not a forward range.");'
#    if namespace:
#        i += "} // namespace " + namespace + "\n"
#    return i



#
# MAIN
#
def write_file(s, filename):
    if path.exists(filename):
        answer = "y"
        # answer = input("File " + filename + "already exists. Overwrite? (y/n): ")
        if answer not in "yY":
            return

    with open(filename, "w") as file:
        file.write(s)


if __name__ == "__main__":
    if not path.isdir(directory):
        mkdir(directory)
    todo = [ [i, j] for i in range(1, MAX_N + 1) for j in range(1, MAX_N + 1)]
    todo.remove([1, 1])  # remove [1, 1]
    for r, c in todo:
        filename = directory + "/" + classname(r, c)
        header, source, templates = generateFiles(r, c)
        if include_template_instantiations:
            write_file(templates, filename + ".tpp")
            source += "\n#include \"" + classname(r, c) + ".tpp\""
        write_file(header, filename + ".hpp")
        write_file(source, filename + ".cpp")

    write_file(generateConceptsFile(MAX_N + 1, MAX_N + 1), directory + "/" + "concepts.hpp")
    # write_file(generateIteratorFile(), directory + "/" + "iterator.hpp")
