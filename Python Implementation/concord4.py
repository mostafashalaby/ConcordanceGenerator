import re


class Concordance:

    def __init__(self, input_name, exclusion_name):
        """
        initializes attributes of Concordance instance
        """
        self.input_name = input_name
        self.exclusion_name = exclusion_name

    @staticmethod
    def __read(filename):
        """
        reads the file specified and returns its lines as a list
        """
        try:
            file_handle = open(filename)
            lines = file_handle.read().rstrip()
            lines_list = lines.split("\n")
            file_handle.close()
            return lines_list
        except FileNotFoundError:
            print("{} couldn't be found.".format(filename))

    @staticmethod
    def __get_keywords(input_list, exclude_list):
        """
        takes input_list, filters out content from exclude_list, and returns a list of 
        sorted, unique, lowercase keywords as per the specifications of the pattern
        """
        keywords = []
        pattobj = re.compile(r"\b([\w'-]+)\b")
         
        for line in input_list:
            for match in pattobj.finditer(line):
                word = match.group(1)
                if (word.lower() not in keywords) and (word.lower() not in exclude_list):
                    keywords.append(word.lower())            
        keywords.sort()
        return keywords
    
    @staticmethod
    def __len_of_keyword(keywords):
        """
        returns an integer representing the length of the longest word in keywords, +2 spaces
        """
        return len(max(keywords, key=len)) + 2

    def __format_word(self, word, keywords):
        """
        returns a capitalized and appropriately spaced version of word
        """
        current_length = len(word)
        wanted_extension = self.__len_of_keyword(keywords) - current_length
    
        word = word.upper()
        while wanted_extension != 0:
            word += " "
            wanted_extension -= 1
    
        return word 
    
    def full_text(self):
        """
        returns a list of strings corresponding to the Concordance output specified
        """
        full_text = []
        input_list = self.__read(self.input_name)
        exclusion_list = self.__read(self.exclusion_name) if self.exclusion_name else []    
        keywords = self.__get_keywords(input_list, exclusion_list)
  
        for word in keywords:
            for i, line in enumerate(input_list):
                pattern = r'\b(?<!-){}(?!-)\b'.format(word)
                pattobj = re.compile(pattern) 
                occurrences = len(pattobj.findall(line.lower()))
                if occurrences:
                    formatted_word = self.__format_word(word, keywords)
                    output = "{}{} ".format(formatted_word, line)
                    output += "({})".format(i+1) if occurrences == 1 else "({}*)".format(i+1)
                    full_text.append(output)

        return full_text
