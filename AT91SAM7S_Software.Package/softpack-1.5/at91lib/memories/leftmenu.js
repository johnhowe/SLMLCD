function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5466\" class=\"headerLeftMenuInActive\"><a id=\"aID5466\" href=\"#\" OnMouseOver=\"link('_dir','memories0',this)\" class=\"leftMenuLinkHeadInActive\">memories</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID5465\" class=\"leftMenuInActive\"><a id=\"aID5465\" href=\"#\" OnMouseOver=\"link('_dir','flash/flash0',this)\" class=\"leftMenuLinkInActive\">flash</a></div>\n");
document.write("<div id=\"divID5467\" class=\"leftMenuInActive\"><a id=\"aID5467\" href=\"#\" OnMouseOver=\"link('_dir','sdmmc/sdmmc0',this)\" class=\"leftMenuLinkInActive\">sdmmc</a></div>\n");
document.write("<div id=\"divID5468\" class=\"leftMenuInActive\"><a id=\"aID5468\" href=\"#\" OnMouseOver=\"link('_dir','spi-flash/spimi_flash0',this)\" class=\"leftMenuLinkInActive\">spi-flash</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Units</div>\n");
document.write("<div id=\"divID5531\" class=\"leftMenuInActive\"><a id=\"aID5531\" href=\"#\" OnMouseOver=\"link('_unit','MEDFlash_h0',this)\" class=\"leftMenuLinkInActive\">MEDFlash.h</a></div>\n");
document.write("<div id=\"divID5532\" class=\"leftMenuInActive\"><a id=\"aID5532\" href=\"#\" OnMouseOver=\"link('_unit','Media_h0',this)\" class=\"leftMenuLinkInActive\">Media.h</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
