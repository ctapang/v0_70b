/*********************************************************************
*
*  Dynamic Variable and No Compression  Configuration Dialog Box.
*
**********************************************************************
* FileName:        AdvanceSettings.java
* Complier:        JAVA version "1.6.0_20 and onwards"
* IDE :            Netbean
* Software License Agreement
*
* Copyright (C) 2012 Microchip Technology Inc.  All rights reserved.
*
* Microchip licenses to you the right to use, modify, copy, and
* distribute the Software when used with a Microchip microcontroller or
* digital signal controller product which is integrated into Licensee's product.
*
* You should refer to the license agreement accompanying this
* Software for additional information regarding your rights and
* obligations.
*
* THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
* WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
* LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
* PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
* MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
* CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
* PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
* BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
* THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
* SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
* (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE
**********************************************************************/

package MicrochipMPFS;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;
import javax.swing.Action;

public class AdvanceSettings extends javax.swing.JDialog {
    MainMPFS  mainMpfs;
    ImageIcon icon = new ImageIcon(getClass().getResource("/Resource/mchpIcon.png"));
    public  int reserveBlock=64;
    public  String DynVarStr = "*.htm, *.html, *.cgi, *.xml";
    public  String NoCompStr = "*.inc, snmp.bib";

    /** Creates new form AdvanceSettings */
    public AdvanceSettings(javax.swing.JFrame parent, boolean modal) {
        super(parent, modal);       
        initComponents();
        /*
        radBtnMPFS2.setVisible(false);
        radBtnMpfsCls.setVisible(false);
         *
         */
        mainMpfs = (MainMPFS)parent;
       
        setIconImage(icon.getImage());
        defaultAdvanceSetting();
        toolTipAdvanceSettings();        

        AdvanceSettingKeyEventActionIntialization();
        DynVarStr = txtDynFiles.getText();
        NoCompStr = txtDoNotCompress.getText();
        
//        Action  ESCactionListener = new AbstractAction () {
//          public void actionPerformed(ActionEvent actionEvent) {
//            setVisible(false);
//            dispose();
//          }
//        };
//        KeyStroke stroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0, true);
//        JComponent comp = this.getRootPane();
//        comp.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(stroke, "ESCAPE");
//        ActionMap actionMap = comp.getActionMap();
//        actionMap.put("ESCAPE", ESCactionListener); //*/
//        //comp.setActionMap(actionMap);
//        comp.getRootPane().setDefaultButton(btnOK);
//        comp.getRootPane().setDefaultButton(btnDefault);
//        comp.getRootPane().setDefaultButton(btnCancel);
    }

    /** This method is called from within the constructor to
     * initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is
     * always regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        buttonGroup1 = new javax.swing.ButtonGroup();
        lblDynFiles = new javax.swing.JLabel();
        txtDynFiles = new javax.swing.JTextField();
        lblDoNotCompress = new javax.swing.JLabel();
        txtDoNotCompress = new javax.swing.JTextField();
        lblTcpIpHelp = new javax.swing.JLabel();
        btnOK = new javax.swing.JButton();
        btnDefault = new javax.swing.JButton();
        btnCancel = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.DISPOSE_ON_CLOSE);
        setTitle("MPFS Processing Advance Settings");
        setLocationByPlatform(true);
        setMinimumSize(new java.awt.Dimension(180, 200));
        setModal(true);
        setResizable(false);

        lblDynFiles.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        lblDynFiles.setText("Dynamic Files:");

        txtDynFiles.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        txtDynFiles.setText("*.htm, *.html, *.cgi, *.xml");

        lblDoNotCompress.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        lblDoNotCompress.setText("Do Not Compress:");

        txtDoNotCompress.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        txtDoNotCompress.setText("*.inc, snmp.bib");

        lblTcpIpHelp.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        lblTcpIpHelp.setText("  ( Reserve block is only configured in TCPIPConfig. )");

        btnOK.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        btnOK.setText("OK");
        btnOK.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnOKActionPerformed(evt);
            }
        });

        btnDefault.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        btnDefault.setText("Default");
        btnDefault.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnDefaultActionPerformed(evt);
            }
        });

        btnCancel.setFont(new java.awt.Font("Microsoft Sans Serif", 0, 11));
        btnCancel.setText("Cancel");
        btnCancel.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCancelActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGap(10, 10, 10)
                        .addComponent(lblDynFiles, javax.swing.GroupLayout.PREFERRED_SIZE, 128, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(btnOK, javax.swing.GroupLayout.PREFERRED_SIZE, 80, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addGap(18, 18, 18)
                        .addComponent(btnDefault, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE)
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED, 22, Short.MAX_VALUE)
                        .addComponent(btnCancel, javax.swing.GroupLayout.PREFERRED_SIZE, 70, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(txtDynFiles, javax.swing.GroupLayout.PREFERRED_SIZE, 260, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(lblDoNotCompress, javax.swing.GroupLayout.PREFERRED_SIZE, 150, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(txtDoNotCompress, javax.swing.GroupLayout.PREFERRED_SIZE, 260, javax.swing.GroupLayout.PREFERRED_SIZE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addComponent(lblTcpIpHelp, javax.swing.GroupLayout.DEFAULT_SIZE, 260, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(10, 10, 10)
                .addComponent(lblDynFiles, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addGap(2, 2, 2)
                .addComponent(txtDynFiles, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(lblDoNotCompress, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(txtDoNotCompress, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(lblTcpIpHelp, javax.swing.GroupLayout.PREFERRED_SIZE, 20, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnOK)
                    .addComponent(btnDefault)
                    .addComponent(btnCancel))
                .addContainerGap(12, Short.MAX_VALUE))
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents


     private void btnOKActionPerformed(java.awt.event.ActionEvent evt) {
        DynVarStr = txtDynFiles.getText();
        txtDynFiles.setText(DynVarStr);
        NoCompStr = txtDoNotCompress.getText();
        txtDoNotCompress.setText(NoCompStr);
        // TODO add your handling code here:
       /* if(radBtnMPFS2.isSelected() == true)
        {
            DynVarStr = txtDynFiles.getText();
            txtDynFiles.setText(DynVarStr);
            NoCompStr = txtDoNotCompress.getText();
            txtDoNotCompress.setText(NoCompStr);
        }
        else
        {
            txtResvBlk.setText(txtResvBlk.getText().toString());
            reserveBlock= Integer.parseInt(txtResvBlk.getText());
        }
        *
        */
        //txtDynFiles.setText("*.htm, *.html, *.cgi");
        //mainMpfs.setFocusable(true);
        dispose();
    }
    
    private void btnDefaultActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        
        defaultAdvanceSetting();
        DynVarStr = "*.htm, *.html, *.cgi, *.xml";
        NoCompStr = "*.inc, snmp.bib";
        txtDynFiles.setText(DynVarStr);
        txtDoNotCompress.setText(NoCompStr);
        if(mainMpfs.radUnifiedStackuse.isSelected())
        {
           NoCompStr = "*.inc, snmp.bib,*.bin";
           txtDoNotCompress.setText(NoCompStr); 
        }
       
        /*
        radBtnMPFS2.setSelected(true);
        txtResvBlk.setText("64");
        reserveBlock= Integer.parseInt(txtResvBlk.getText());
         *
         */
       // mainMpfs.txtProjectImageName.setText("MPFSImg2");
    }

    private void btnCancelActionPerformed(java.awt.event.ActionEvent evt) {
        // TODO add your handling code here:
        txtDynFiles.setText(DynVarStr);
        txtDoNotCompress.setText(NoCompStr);

        /*
        if(getRadBtnMpfs2Status())
        {
        txtDynFiles.setText(DynVarStr);
        txtDoNotCompress.setText(NoCompStr);
        }
        else if(getRadBtnMpfsClassicStatus())
        {
            //txtResvBlk.setText(Integer.toString(reserveBlock));
        }
         *
         */
        dispose();
    }/*
    private void btnOKActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnOKActionPerformed
        // TODO add your handling code here:
    }//GEN-LAST:event_btnOKActionPerformed

private void btnDefaultActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnDefaultActionPerformed
// TODO add your handling code here:
}//GEN-LAST:event_btnDefaultActionPerformed

private void btnCancelActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCancelActionPerformed
// TODO add your handling code here:
}//GEN-LAST:event_btnCancelActionPerformed

 */
    public void defaultAdvanceSetting()
    {
        txtDoNotCompress.setVisible(true);
        txtDynFiles.setVisible(true);
        lblDynFiles.setVisible(true);
        lblDoNotCompress.setVisible(true);
        
        if(mainMpfs.radUnifiedStackuse.isSelected())
        {
           NoCompStr = "*.inc, snmp.bib,*.bin";
           txtDoNotCompress.setText(NoCompStr); 
        }
        else
        {
            NoCompStr = "*.inc, snmp.bib";
            txtDoNotCompress.setText(NoCompStr);
        }
        if(!mainMpfs.radUnifiedStackuse.isEnabled())
        {
            lblTcpIpHelp.setText("(Reserve block is only " +
                            "configured in TCPIPConfig.)");
        }
        //mainMpfs.txtProjectImageName.setText("MPFSImg2");
        /*
        //commonFalse();
        if(radBtnMPFS2.isSelected())
        {
            txtDoNotCompress.setVisible(true);
            txtDynFiles.setVisible(true);
            lblDynFiles.setVisible(true);
            lblDoNotCompress.setVisible(true);

            lblTcpIpHelp.setText("(Reserve block is only " +
                                "configured in TCPIPConfig.)");
            lblResvBlk.setVisible(false);
            txtResvBlk.setVisible(false);
            lblBytes.setVisible(false);
            mainMpfs.txtProjectImageName.setText("MPFSImg2");
        }
        else
        {
            txtDoNotCompress.setVisible(false);
            txtDynFiles.setVisible(false);
            lblDynFiles.setVisible(false);
            lblDoNotCompress.setVisible(false);
            lblTcpIpHelp.setText("(Reserve block MUST match TCPIPConfig.)");
            lblResvBlk.setVisible(true);
            txtResvBlk.setVisible(true);
            lblBytes.setVisible(true);
            mainMpfs.txtProjectImageName.setText("MPFSImg");

        }
         *
         */
    }

    void commonFalse()
    {
        txtDoNotCompress.setVisible(false);
        txtDynFiles.setVisible(false);
        lblDynFiles.setVisible(false);
        lblDoNotCompress.setVisible(false);
        //lblTCPIP.setText("(Reserve block is only " +
            //                "configured in TCPIPConfig.)");
        /*lblResvBlk.setVisible(false);
        txtResvBlk.setVisible(false);
        lblBytes.setVisible(false);
         *
         */
    }
    void commontrue()
    {
        txtDoNotCompress.setVisible(true);
        txtDynFiles.setVisible(true);
        lblDynFiles.setVisible(true);
        lblDoNotCompress.setVisible(true);
        //lblTCPIP.setText("(Reserve block is only " +
            //                "configured in TCPIPConfig.)");
        /*lblResvBlk.setVisible(true);
        txtResvBlk.setVisible(true);
        lblBytes.setVisible(true);
         *
         */
    }
    /*
    boolean getRadBtnMpfs2Status()
    {
        return radBtnMPFS2.isSelected();
    }
    boolean getRadBtnMpfsClassicStatus()
    {
        return radBtnMpfsCls.isSelected();
    }
      *
      */

    public void setDynamicFileStr(String dynamicVarStr)
    {
        txtDynFiles.setText(dynamicVarStr);
        DynVarStr = txtDynFiles.getText();
    }

    public void setNoCompressionFileStr(String noCompressStr)
    {
        txtDoNotCompress.setText(noCompressStr);
        noCompressStr = txtDoNotCompress.getText();
    }

    public String getDynamicFileStr()
    {
        return txtDynFiles.getText();
    }

    public String getNoCompressionFileStr()
    {
        return txtDoNotCompress.getText();
    }

    void toolTipAdvanceSettings()
    {
        String infoString;
        /*infoString = "<html><body bgcolor=\"#FFFFCC\"><img src=\""+ getClass()
                     .getResource("/Resource/info.gif") + "\"> <b>";*/
        infoString = "<html><body bgcolor=\"#FFFFCC\"> <b>";

        infoString = infoString + "<headings> <font size=\"4\">"
                +" Advanced Settings Help </font></headings></b><br>";
        /*
        radBtnMPFS2.setToolTipText(infoString +
                "Build an MPFS2 image that is compatible <br>with " +
                "the HTTP2 web server." + "</body></html>");

        radBtnMpfsCls.setToolTipText(infoString +
                "Build a classic MPFS image that is compatible <br>" +
                "with the original HTTP web server." + "</body></html>");

        txtResvBlk.setToolTipText(infoString +"The MPFS image will begin " +
                "at this address <br>in your external storage.  Memory befor" +
                    "e this address <br>will be reserved for your own " +
                    "application\'s use. <br>uploaded to external storage," +
                    "<br>such as EEPROM or serial Flash."+"</body></html>" );

         *
         */
        txtDynFiles.setToolTipText(infoString + "These files will be searched " +
                "for<br>dynamic variables and indexed for <br>your applic" +
                "ation.  Enter file names or<br>extensions, separated by " +
                "commas. <br>for the remainder of the process."+"</body></html>");

       

        txtDoNotCompress.setToolTipText(infoString+"By default, MPFS2 will compress" +
                " any file <br>without dynamic variables.These files can <br> " +
                "be served to web browsers, but cannot be <br>" +
                "read by the device.Files that need to be <br>" +
                "accessed locally should not be compressed.<br>" +
                "Enter file names or extentions."+"</body></html>");
    }

    private void AdvanceSettingKeyEventActionIntialization()
    {

        Action  ESCactionListener = new AbstractAction () {
          public void actionPerformed(ActionEvent actionEvent) {
            setVisible(false);
            dispose();
          }
          
        };
        KeyStroke stroke = KeyStroke.getKeyStroke(KeyEvent.VK_ESCAPE, 0, true);
        JComponent comp = this.getRootPane();
        comp.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW).put(stroke, "ESCAPE");
        ActionMap actionMap = comp.getActionMap();
        actionMap.put("ESCAPE", ESCactionListener);

        /* OK button Action Solves MAC , Linux and Window enter key issue*/
        Action  OKactionListener = new AbstractAction () {
          public void actionPerformed(ActionEvent actionEvent) {
            btnOKActionPerformed(actionEvent);
          }
        };
         /* Cancel button Action Solves MAC , Linux and Window enter key issue*/
        Action  CancelactionListener = new AbstractAction () {
          public void actionPerformed(ActionEvent actionEvent) {
            btnCancelActionPerformed(actionEvent);
          }
        };
         /* Default button Action Solves MAC , Linux and Window enter key issue*/
        Action  DefaultactionListener = new AbstractAction () {
          public void actionPerformed(ActionEvent actionEvent) {
            btnDefaultActionPerformed(actionEvent);
          }
        };
        KeyStroke enter_ok = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0, true);
        KeyStroke enter_default = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0, true);
        KeyStroke enter_cancel = KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0, true);

        btnOK.getInputMap(JButton.WHEN_FOCUSED).put(enter_ok, "OK");
        btnDefault.getInputMap(JButton.WHEN_FOCUSED).put(enter_default, "deafult");
        btnCancel.getInputMap(JButton.WHEN_FOCUSED).put(enter_cancel, "cancel");
        actionMap = btnOK.getActionMap();
        actionMap.put("OK", OKactionListener);
        btnOK.setActionMap(actionMap);

        actionMap = btnDefault.getActionMap();
        actionMap.put("deafult", DefaultactionListener);
        btnDefault.setActionMap(actionMap);

        actionMap = btnCancel.getActionMap();
        actionMap.put("cancel", CancelactionListener);
        btnCancel.setActionMap(actionMap);
    }
    /**
    * @param args the command line arguments
    */
    /*
    public static void main(String args[]) {
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                AdvanceSettings dialog = new AdvanceSettings(new javax.swing.JFrame(), true);
                dialog.addWindowListener(new java.awt.event.WindowAdapter() {
                    public void windowClosing(java.awt.event.WindowEvent e) {
                        System.exit(0);
                    }
                });
                dialog.setVisible(true);
            }
        });
    }
*/
    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnCancel;
    private javax.swing.JButton btnDefault;
    private javax.swing.JButton btnOK;
    private javax.swing.ButtonGroup buttonGroup1;
    private javax.swing.JLabel lblDoNotCompress;
    private javax.swing.JLabel lblDynFiles;
    private javax.swing.JLabel lblTcpIpHelp;
    private javax.swing.JTextField txtDoNotCompress;
    private javax.swing.JTextField txtDynFiles;
    // End of variables declaration//GEN-END:variables

}
