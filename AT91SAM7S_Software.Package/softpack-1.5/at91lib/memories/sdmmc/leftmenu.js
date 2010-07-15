function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID5467\" class=\"headerLeftMenuInActive\"><a id=\"aID5467\" href=\"#\" OnMouseOver=\"link('_dir','sdmmc0',this)\" class=\"leftMenuLinkHeadInActive\">sdmmc</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Pages</div>\n");
document.write("<div id=\"divID5340\" class=\"leftMenuInActive\"><a id=\"aID5340\" href=\"#\" OnMouseOver=\"link('_page','sdcardspimodeinitializationandidentification0',this)\" class=\"leftMenuLinkInActive\">sdcard spi mode initialization and identification</a></div>\n");
document.write("<div id=\"divID5342\" class=\"leftMenuInActive\"><a id=\"aID5342\" href=\"#\" OnMouseOver=\"link('_page','sdcardspimoderead0',this)\" class=\"leftMenuLinkInActive\">sdcard spi mode read</a></div>\n");
document.write("<div id=\"divID5341\" class=\"leftMenuInActive\"><a id=\"aID5341\" href=\"#\" OnMouseOver=\"link('_page','sdcardspimodewrite0',this)\" class=\"leftMenuLinkInActive\">sdcard spi mode write</a></div>\n");
document.write("<div id=\"divID5343\" class=\"leftMenuInActive\"><a id=\"aID5343\" href=\"#\" OnMouseOver=\"link('_page','sdhc0',this)\" class=\"leftMenuLinkInActive\">sdhc</a></div>\n");
document.write("<div id=\"divID5339\" class=\"leftMenuInActive\"><a id=\"aID5339\" href=\"#\" OnMouseOver=\"link('_page','sdmmc_spi0',this)\" class=\"leftMenuLinkInActive\">sdmmc_spi</a></div>\n");
document.write("<div id=\"divID5344\" class=\"leftMenuInActive\"><a id=\"aID5344\" href=\"#\" OnMouseOver=\"link('_page','sdspi0',this)\" class=\"leftMenuLinkInActive\">sdspi</a></div>\n");
if(divID != "" && aID != "")
{
document.getElementById(divID).className = divClassName;
document.getElementById(aID).className = aClassName;
}
}
