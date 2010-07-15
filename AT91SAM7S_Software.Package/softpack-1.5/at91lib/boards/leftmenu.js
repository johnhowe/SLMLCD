function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5459\" class=\"headerLeftMenuInActive\"><a id=\"aID5459\" href=\"#\" OnMouseOver=\"link('_dir','boards0',this)\" class=\"leftMenuLinkHeadInActive\">boards</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5458\" class=\"leftMenuInActive\"><a id=\"aID5458\" href=\"#\" OnMouseOver=\"link('_dir','at91sam7s-ek/at91sam7smi_ek0',this)\" class=\"leftMenuLinkInActive\">at91sam7s-ek</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
