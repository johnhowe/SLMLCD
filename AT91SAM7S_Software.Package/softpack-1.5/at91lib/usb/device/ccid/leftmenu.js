function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5490\" class=\"headerLeftMenuInActive\"><a id=\"aID5490\" href=\"#\" OnMouseOver=\"link('_dir','ccid0',this)\" class=\"leftMenuLinkHeadInActive\">ccid</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5586\" class=\"leftMenuInActive\"><a id=\"aID5586\" href=\"#\" OnMouseOver=\"link('_unit','cciddriver_c0',this)\" class=\"leftMenuLinkInActive\">cciddriver.c</a></div>\n");
document.write("<div id=\"divID5587\" class=\"leftMenuInActive\"><a id=\"aID5587\" href=\"#\" OnMouseOver=\"link('_unit','cciddriver_h0',this)\" class=\"leftMenuLinkInActive\">cciddriver.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
