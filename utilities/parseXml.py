import os.path
import xmltodict, json
from xml.dom import minidom

def main():
    dictionary = {'a': [], 'b': [], 'c': [], 'd': [], 'e': [], 'f': [], 'g': [], 'h': [], 'i': [], 'j': [], 'k': [], 'l': [], 'm': [], 'n': [], 'o': [], 'p': [], 'q': [], 'r': [], 's': [], 't': [], 'u': [], 'v': [], 'w': [], 'x': [], 'y': [], 'z': []}
    xmldoc = minidom.parse('ipa.xml')
    itemlist = xmldoc.getElementsByTagName('ss:Row')
    for s in itemlist:
        item = s.getElementsByTagName('Data')
        key = item[0].firstChild.data
        if ' ' in key:
            continue
        val = item[1].firstChild.data
        dictionary[key[0].lower()].append({'key': key, 'val': val})
        # print(item[0].firstChild.data)
    for letter in dictionary:
        with open('../Resources/properties/database/dictionary/'+ letter + '.json', 'w') as outfile:
            json.dump(dictionary[letter], outfile)

if __name__ == '__main__':
    main()