#!/bin/bash

rm -rf ./dumpz/

readme="README.md"
rm "$readme"
echo "| Comment | Language | Date |" >> "$readme"
echo "| ------- | -------- | ---- |" >> "$readme"

declare -A lang_ext
lang_ext["C"]=".c"
lang_ext["Python 3"]=".py"
lang_ext["Scheme"]=".scm"

url="https://dumpz.org/users/aqshvartz/"
input_file_name="aqshvartz.html"

#wget -O "$input_file_name" "$url"

# $ man grep
#
#        -z, --null-data
#              Treat the input as a set of lines, each terminated by a zero  byte  (the  ASCII  NUL  character)  instead  of  a
#              newline.   Like the -Z or --null option, this option can be used with commands like sort -z to process arbitrary
#              file names.
#

# https://ss64.com/bash/read.html
#   -d delim
#             The first character of delim is used to terminate the input line, rather than newline.


cat "$input_file_name" | grep -P -o -z '(?<=class="dump">\n)(.*\n){7}' | while read -d '' line ; do

    dump_url=$(echo "$line" | grep -P -o '(?<=href=").*(?=")')
    id=$(echo "$dump_url" | grep -P -o '\d*')
    
    comment=$(echo "$line" | grep -P -o '(?<=class="comment">)(.*)(?=<\/td>)')
    
    lexer=$(echo "$line" | grep -P -o '(?<=class="lexer">)(.*)(?=<\/td>)')
    
    date=$(echo "$line" | grep -P -o '(?<=class="date col-md-1">)(.*)(?=<\/td>)')
    
    #echo "$dump_url;$id;$comment;$lexer;${lang_ext[$lexer]};$date"
    
    filename=$id
    filename+=${lang_ext[$lexer]}  # https://www.artificialworlds.net/blog/2012/10/17/bash-associative-array-examples/
    
    output_file_path="dumpz/$id/$filename"
    
    src_url=$dump_url
    src_url+="text/"
    
    curl "$src_url" --create-dirs -o "./$output_file_path" --silent --location  # https://curl.haxx.se/docs/faq.html#301_Moved_Permanently
    
    echo "| [$comment]($output_file_path) | $lexer | $date |" >> "$readme"

done
