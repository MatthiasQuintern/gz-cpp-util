#!/bin/python3
"""
A python script to generate toString functions for all enumerations in a cpp file.
Copyright  ©  2022  Matthias  Quintern.
This software comes with no warranty.
This software is licensed under the GPL3
"""
from os import path, listdir, chdir
from sys import argv, exit
import re


# search in header files for enums 
header_filetypes = [".hpp"]
# definition are written to source file having the same name as the header
source_filetype = ".cpp"

def error(s):
    print(s)
    exit(1)

constexpr = "constexpr"
inline = "inline"
static = "static"

def template_str2list(s:str):
    if s:
        templates = s.removeprefix("template<").removesuffix(">").split(", ")
        templates = [ t.split(" ") for t in templates ]
    else:
        templates = []
    return templates

def template_list2str(t:list[tuple[str, str]], req:str=""):
    if len(t) == 0:
        return ""
    s = "template<"
    for temp in t:
        s += temp[0] + " " + temp[1] + ", "
    s = s.removesuffix(", ") + ">\n"
    if req:
        s += "\t" + "requires " + req
    return s

def transformString(s: str, depth: int):
    """Add tabs after all but the last line break and before the first char.
    Do not add tabs to lines that start with a label"""
    new_s = ""
    for line in s.split("\n"):
        if re.fullmatch(r"\w+:[^:].*", line) is None:
            new_s += depth * "\t";
        new_s += line + "\n"
    new_s = new_s.removesuffix("\n").removesuffix(depth*"\t")
    # return depth * tab + s.replace("\n", "\n" + depth * tab, s.count("\n") - 1)
    return new_s


class Member:
    def __init__(self, name:str, m_temp:list=[], prefixes:list=[], ret_type:str="", args:str="", init:str="", requires:str="", const=False, defined=False, is_value=False, namespace:str=""):
        """
        :param name: member name
        :param m_temp: list of templates of the member
        :param prefixes:  things like constexpr, inline...
        :param ret_type: return type of the member
        :param args: arguments of the member
        :param init: initializion of the member
        :param requires: constraints on template types
        :param const: True if the method does not change the object
        :param defined: method defined
        :param is_value: wether the member is a value or a method

        template<c_temp>
        class class {
            comment
            template<m_temp>
            prefixes ret_type name(args) const : init {
                body
            }
        }
        """
        self.name = name
        self.prefixes = prefixes
        self.m_temp = m_temp
        self.ret_type = ""
        if ret_type: self.ret_type = ret_type + " "
        self.args = args
        self.init = ""
        if init: self.init = f"\n\t : {init} "
        self.requires = requires
        self.const = ""
        if const: self.const = " const"
        self.defined = defined
        self.comment = ""
        # if comment:
        #     if type(comment) == str:
        #         self.comment = "/// " + comment + "\n"
        #     elif type(comment) == dict:
        #         self.comment = comment_from_dict(comment)
        self.is_value = is_value
        self.namespace = namespace

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

    def get_source_name(self, c_temp=[], class_=""):
        s = ""
        if class_:
            if len(c_temp) > 0:
                class_ = class_ + "<"
                for t in c_temp:
                    class_ += f"{t[1]}, "
                class_ = class_.removesuffix(", ") + ">"
            class_ += "::"

        s += template_list2str(self.m_temp, self.requires)
        for p in self.prefixes:
            s += p + " "

        if self.is_value:
            if static in self.prefixes and not constexpr in self.prefixes:
                s += f"{self.ret_type}{class_}{self.name};\n"
                return s
            else:
                s += f"{self.ret_type}{class_}{self.name};\n"
                return s
        s += f"{self.ret_type}{class_}{self.name}({self.args}){self.const}"
        return s

    def source(self, c_temp=[], class_="", depth:int=0):
        """
        Return the empty defition + declarations for a source file
        """
        s = ""
        if class_:
            s += template_list2str(c_temp)
            if len(c_temp) > 0:
                class_ = class_ + "<"
                for t in c_temp:
                    class_ += f"{t[1]}, "
                class_ = class_.removesuffix(", ") + ">"
            class_ += "::"

        s += template_list2str(self.m_temp, self.requires)
        for p in self.prefixes:
            s += p + " "

        if self.is_value:
            if static in self.prefixes and not constexpr in self.prefixes:
                s += f"{self.ret_type}{class_}{self.name};\n"
                return s
            else:
                return ""

        s += f"{self.ret_type}{class_}{self.name}({self.args}){self.const}{self.init}" + " {\n\t\n}\n"
            # s += " {\n"
            # body = ""
            # for l in self.body: body += l + "\n"
            # s += transformString(body, depth)
            # s += "}\n"
        # else:
            # s += "{}"
        return transformString(s, depth)

    def __repr__(self):
        return self.get_source_name([], "")


class Class:
    def __init__(self, name: str, c_temp: list[str]):
        self.member_functions: list[Member] = []
        self.member_variables: list[Member] = []
        self.name = name
        self.c_temp: list[str] = c_temp


#
# regex
#
# s must be a string where all indentation was removed
# COMMENTS
def starts_with_normal_comment(s: str) -> bool:
    if re.search(r"^(//|/?\*)[^*/]", s): return True
    else: return False

def starts_with_doxygen_comment(s: str) -> bool:
    if re.search(r"^(///|/\*\*)", s): return True
    else: return False

def starts_with_comment(s: str) -> bool:
    return starts_with_normal_comment(s) or starts_with_doxygen_comment(s);

def starts_with_comment_end(s: str) -> bool:
    if re.search(r"^(\*/)", s): return True
    else: return False

# NAMESPACE
def namespace_open(s: str) -> tuple[bool, str]:
    match = re.search(r"^namespace (\w+) *{", s)
    if match:
        return True, match.groups()[0]
    return False, ""


# TEMPLATE
def template_declaration(s: str) -> bool:
    if re.search(r"^template<(.+)>", s):
        return True
    return False

# CLASS DECLARATION
def class_declaration(s: str) -> tuple[bool, str]:
    match = re.search(r"^class (\w+)", s)
    if match:
        return True, match.groups()[0]
    return False, ""

# VARIABLE/MEMBER DECLARATION
def variable_declaration(s: str, template_str:str = "", namespace:str="") -> tuple[bool, Member]:
    match = re.search(r"^(\w+ )+(\w+)( *= *.+)? *;", s)
    # match = re.search(r"^((?:\w+ )+)(\w+) *(const)? *;", s)  # declration
    if match:
        g = match.groups()
        prefixes = []
        ret_type = ""
        if g[2]: defined = True
        else: defined = False
        # get ret_type and prefixes
        for prefix in g[0].strip(" ").split(" "):
            if prefix in ["const", "constexpr", "inline", "static"]:
                prefixes.append(prefix)
            else:
                ret_type += prefix + " "
        return True, Member(g[1], m_temp=template_str2list(template_str), prefixes=prefixes, ret_type=ret_type, is_value=True, defined=defined, namespace=namespace)
    return False, Member("")

# FUNCTION DECLARATION
def function_declaration(s: str, template_str:str = "", namespace: str="") -> tuple[bool, Member]:
    match = re.search(r"^((?:\w+ )+)(\w+)\(((?:\w+ )*(?:\w+))?\) *(const)? *;", s)  # declration
    if match is None:
        match = re.search(r"^((?:\w+ )+)(?:\w+)\(((?:\w+ )*(?:\w+))?\) *(const)? * *{", s)  # declaration with definition
        defined = True
    else:
        defined = False
    if match:
        g = match.groups()
        prefixes = []
        ret_type = ""
        # get ret_type and prefixes
        for prefix in g[0].strip(" ").split(" "):
            if prefix in ["const", "constexpr", "inline", "static"]:
                prefixes.append(prefix)
            else:
                ret_type += prefix + " "
        ret_type = ret_type.strip(" ")
        if g[2]: args = g[2]
        else: args = ""
        if g[3]: const = True
        else: const = False


        ret_type = ""
        return True, Member(g[1], template_str2list(template_str), prefixes=prefixes, ret_type=ret_type, args=args, defined=defined, const=const, namespace=namespace)
    return False, Member("")


#
# INDENTATION
# 
def get_indentation(s_indentation: str) -> int:
    """
    returns number of spaces
    """
    return s_indentation.replace("\t", "    ").count(" ")

def get_string_and_indent(s: str) -> tuple[str, int]:
    """
    returns the string without indentation and the number of spaces in the indentation
    """
    match = re.search("^([ \t]*)", s)
    if match:
        return s[len(match.groups()[0]):], get_indentation(match.groups()[0])
    return s, 0


# SCOPE END
def scope_end(s: str) -> bool:
    if re.search(r"^}", s):
        return True
    return False

def parse_header(header_file:str):
    with open(header_file, "r") as file:
        header = file.readlines()

    declarations: list[Class | Member] = []

    template_str = ""
    scopes : list[tuple[str, str, int, int]] = []   # type (eg class, namespace...), name, indentation, line
    in_class = ""
    namespace = ""

    for i in range(len(header)):
        line, indent = get_string_and_indent(header[i])
        if starts_with_normal_comment(line): continue
        if starts_with_doxygen_comment(line):
            pass
        if starts_with_comment_end(line):
            pass

        if template_declaration(line):
            template_str = line

        match, name = namespace_open(line)
        if match:
            scopes.append(("namespace", name, indent, i))
            namespace += "::" + name
            namespace = namespace.strip("::")

        match, name = class_declaration(line)
        if match:
            # print("class in", i, "-", name)
            scopes.append(("class", name, indent, i))
            declarations.append(Class(name, c_temp=template_str2list(template_str)))
            in_class = name
            # declarations[-1].members.append(member_from_str(line, template_str))
        match, member = function_declaration(line, template_str, namespace)
        if match:
            # print("function in", i, "-", member.get_source_name([], ""))
            if in_class:
                declarations[-1].member_functions.append(member)
            else:
                declarations.append(member)
            template_str = ""
        match, member = variable_declaration(line, template_str, namespace)
        if match:
            # print("variable in", i, "-", member.get_source_name([], ""))
            if in_class:
                declarations[-1].member_variables.append(member)
            else:
                declarations.append(member)
            template_str = ""

        if scope_end(line):
            if len(scopes) > 0 and scopes[-1][2] == indent:
                if (scopes[-1][0] == "namespace"):
                    for i in range(len(namespace)):
                        if namespace[-i-1] == ":":
                            namespace = namespace[:-i-2]
                            break;
                scopes.pop()
            else:
                # print("WARNING: Found scope end but no scope was opened at this indentaiton. line:", i)
                pass
    return declarations


def get_definition(declarations: list[Class | Member], target_name: str):
    member = None
    for dec in declarations:
        if type(dec) == Class:
            for mem in dec.member_functions:
                if mem.name in target_name:
                    return mem.source(dec.c_temp, dec.name, len(mem.namespace.split("::")))
        else:
            if dec.name in target_name:
                return dec.source([], "", len(dec.namespace.split("::")))

    return ""


def print_help():
    print("""
Synposis:           gen_definitions.py <Options>... --file <file> --name <name>
-h --help           help
--getter
--setter
--getter-and-setter
--def
--name <name>
--file <file>
--no-docs           turn off docstring generation
""")

# def missing_arg(arg):
#     print("Missing argument for", arg)
#     exit(1)

if __name__ == "__main__":
    docs = True
    getter = False
    setter = False
    definition = False
    file = ""
    target_name = ""
    i = 1
    while i in range(1, len(argv)):
        if  argv[i] == "--help" or argv[i] == "-h":
            print_help()
            exit(0)
        elif argv[i] == "--getter-and-setter":
            getter = True
            setter = True
        elif argv[i] == "--getter":
            getter = True
        elif argv[i] == "--setter":
            setter = True
        elif argv[i] == "--def":
            definition = True
            interactive = True
        elif argv[i] == "--no-docs":
            docs = False
        elif argv[i-1] == "--file":
            file = argv[i]
        elif argv[i-1] == "--name":
            target_name = argv[i]
        i += 1

    ret = ""
    declarations = []
    if file:
        if path.isfile(file):
            declarations = parse_header(file)
        else:
            # print("Not a file:", file)
            exit(1)
    if getter:
        pass
    if setter:
        pass
    if definition:
        print(get_definition(declarations, target_name))

