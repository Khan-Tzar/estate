<!DOCTYPE html>
<html lang="en">
<!-- Header -->
<?php $this->header->publish();?>

<!-- /Header -->

  <body class="nav-md">
    <div class="container body">
      
      
      <div class="main_container">
        <!-- Side bar -->
        <?php $this->sideBar->publish();?>
        <?php //exit;?>
        <!-- /Side bar -->
        <!-- top navigation -->
        <?php $this->topNav->publish(); ?>
        <!-- /top navigation -->

        <!-- page content -->
        <div class="right_col" role="main">
	      <div align="center">
        	<img class="" title="" src="<?=WEB_DIR?>/images/logo.png">
          </div>

         

     
           <div class="mainBody">
    <h1 class="home">QUALITY MANUAL<br />
      Standard: ISO 9001:2008 <br />
    </h1>
   
    <img src="<?=WEB_ROOT?>/images/codixLogo.gif" /><br />
    <strong>CO</strong>mpagnie de <strong>D</strong>istribution <strong>I</strong>nformatique e<strong>X</strong>pert<br />
		  Company for distribution of expert automated data processing
    <div class="clear">&nbsp;</div>
    <div class="clear">&nbsp;</div>
    <img src="<?=WEB_ROOT?>/images/imxLogo.gif" /><br />
    <strong>i</strong>nternet / <strong>i</strong>ntranet <strong>M</strong>anager e<strong>X</strong>pert<br />
    Event-driven Management of Cases
    <div style="padding:20px 0px">
      <p><strong>Scope: </strong>Design, Development, Analysis, Specification, Testing, Implementation, Maintenance and Supervision of software solutions</p>
      <p><strong>Document Name: </strong>QUALITY MANUAL<br />
        <br />
        <strong>Author:</strong> Zornitsa KRASTEVA<br />
        <strong>Approved by General Manager:</strong> Laurent TABOUELLE<br />
        <br />
        <strong>Date Last Revision:</strong> 27/11/2013<br />
        <strong>Date Creation:</strong> 30/06/2009<br />
      </p>
    <p><div class="clear">&nbsp;</div></p>
  </div>
  <div class="clearMini">&nbsp;</div>
</div>



        </div>
        <!-- /page content -->

        <!-- footer content -->
        <?php $this->footer->publish(); ?>
        <!-- /footer content -->
      </div>
    </div>
     <?php $this->vendorLibraries->publish(); ?>
    
	
  </body>
</html>
