" Vim syntax file
" Language: johnsonscript
" Written by: Alex Johnson
" 2/19/2019

if exists("b:current_syntax")
    finish
endif

" Keywords
syn keyword builtIns print open newarray getarray setarray getarg getargcount openfile readinteger atfileend closefile 
syn keyword conditionals if else while
syn keyword definition def nextgroup=ID skipwhite
syn keyword definition var 
syn keyword bool True False

" Matches
syn match ID '\h\w*' display contained

syn match comment "#.*$"

syn match int '\d\+'
syn match int '-\d\+'

syn region string start='"' end='"'

" Highlights
let b:current_syntax = "johns"

hi def link builtIns Function
hi def link conditionals Conditional 
hi def link definition Statement

hi def link comment Comment
hi def link int Constant
hi def link string Constant
hi def link bool Constant
hi def link ID Function
