function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5457\" class=\"headerLeftMenuInActive\"><a id=\"aID5457\" href=\"#\" OnMouseOver=\"link('_dir','at91sam7s1280',this)\" class=\"leftMenuLinkHeadInActive\">at91sam7s128</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
