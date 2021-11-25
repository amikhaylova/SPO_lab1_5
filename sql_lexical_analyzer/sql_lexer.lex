%{
#include <stdio.h>
#include "../sql_grammar/y.tab.h"
%}

%%
select					return SELECT;
SELECT					return SELECT;
create					return CREATE;
CREATE					return CREATE;
insert					return INSERT;
INSERT					return INSERT;
update					return UPDATE;
UPDATE					return UPDATE;
delete					return DELETE;
DELETE					return DELETE;
drop					return DROP;
DROP					return DROP;
table					return TABLE;
TABLE					return TABLE;
int					return INT_TYPE;
INT					return INT_TYPE;
uint					return UINT_TYPE;
UINT					return UINT_TYPE;
number					return NUMBER_TYPE;
NUMBER					return NUMBER_TYPE;
text					return TEXT_TYPE;
TEXT					return TEXT_TYPE;
from					return FROM;
FROM					return FROM;
into					return INTO;
INTO					return INTO;
where					return WHERE;
WHERE					return WHERE;
and						return AND;
AND						return AND;
set                     return SET;
SET                     return SET;
values                     return VALUES;
VALUES                     return VALUES;
[ \t\r\n]+		        /* ignore whitespace */;
\*						return ALL;
-?[a-zA-Z0-9]*[.]?[0-9]*	yylval.text=strdup(yytext);return IDENTIFIER;
.                       return (int) yytext[0];
%%

void set_input_string(const char* in) {
  yy_scan_string(in);
}

void end_lexical_scan(void) {
  yy_delete_buffer(YY_CURRENT_BUFFER);
}