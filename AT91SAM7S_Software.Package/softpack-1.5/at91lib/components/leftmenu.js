function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5460\" class=\"headerLeftMenuInActive\"><a id=\"aID5460\" href=\"#\" OnMouseOver=\"link('_dir','components0',this)\" class=\"leftMenuLinkHeadInActive\">components</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5461\" class=\"leftMenuInActive\"><a id=\"aID5461\" href=\"#\" OnMouseOver=\"link('_dir','iso7816/iso78160',this)\" class=\"leftMenuLinkInActive\">iso7816</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
