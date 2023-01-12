// blank: 1, code: 2, comments: 1, code with comments: 2, total: 6

const char* a = "some text // this is not a comment"; // and this is
const char* b = "some text /* this is not a comment */"; /* and this is */
const char* c = "some text \" /* this is not a comment ";
and this is still not