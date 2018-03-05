def string(s):
    s = s.lower()
    dict = {}
    for i in range(len(s)):
        if s[i].isspace() or s[i].isdigit():
            continue
        elif s[i].isalpha():
            if s[i] in dict:
                dict[s[i]] += 1
            else:
                dict[s[i]] = 1

    for key in dict:
        print (key + "  " + str(dict[key]))

string(input())
