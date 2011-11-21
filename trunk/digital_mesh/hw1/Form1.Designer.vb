<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form 覆寫 Dispose 以清除元件清單。
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    '為 Windows Form 設計工具的必要項
    Private components As System.ComponentModel.IContainer

    '注意: 以下為 Windows Form 設計工具所需的程序
    '可以使用 Windows Form 設計工具進行修改。
    '請不要使用程式碼編輯器進行修改。
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container
        Me.MenuStrip1 = New System.Windows.Forms.MenuStrip
        Me.FileToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.OpenToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.SaveToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChoosePointToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseVertexToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseEdgeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseFaceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.VertexRingToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.EdgeRingToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.FaceRingToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowVertexToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowEdgeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowFaceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.CameraToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ResetToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.PictureBox = New System.Windows.Forms.PictureBox
        Me.OpenMeshFileDialog = New System.Windows.Forms.OpenFileDialog
        Me.SaveMeshFileDialog = New System.Windows.Forms.SaveFileDialog
        Me.RenderTimer = New System.Windows.Forms.Timer(Me.components)
        Me.MenuStrip1.SuspendLayout()
        CType(Me.PictureBox, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.ChooseToolStripMenuItem, Me.ShowToolStripMenuItem, Me.CameraToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(667, 25)
        Me.MenuStrip1.TabIndex = 0
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.OpenToolStripMenuItem, Me.SaveToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(39, 21)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'OpenToolStripMenuItem
        '
        Me.OpenToolStripMenuItem.Name = "OpenToolStripMenuItem"
        Me.OpenToolStripMenuItem.Size = New System.Drawing.Size(108, 22)
        Me.OpenToolStripMenuItem.Text = "Open"
        '
        'SaveToolStripMenuItem
        '
        Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
        Me.SaveToolStripMenuItem.Size = New System.Drawing.Size(108, 22)
        Me.SaveToolStripMenuItem.Text = "Save"
        '
        'ChooseToolStripMenuItem
        '
        Me.ChooseToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ChoosePointToolStripMenuItem, Me.ChooseVertexToolStripMenuItem, Me.ChooseEdgeToolStripMenuItem, Me.ChooseFaceToolStripMenuItem, Me.VertexRingToolStripMenuItem, Me.EdgeRingToolStripMenuItem, Me.FaceRingToolStripMenuItem})
        Me.ChooseToolStripMenuItem.Name = "ChooseToolStripMenuItem"
        Me.ChooseToolStripMenuItem.Size = New System.Drawing.Size(64, 21)
        Me.ChooseToolStripMenuItem.Text = "Choose"
        '
        'ChoosePointToolStripMenuItem
        '
        Me.ChoosePointToolStripMenuItem.Name = "ChoosePointToolStripMenuItem"
        Me.ChoosePointToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ChoosePointToolStripMenuItem.Text = "Point"
        '
        'ChooseVertexToolStripMenuItem
        '
        Me.ChooseVertexToolStripMenuItem.Name = "ChooseVertexToolStripMenuItem"
        Me.ChooseVertexToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ChooseVertexToolStripMenuItem.Text = "Vertex"
        '
        'ChooseEdgeToolStripMenuItem
        '
        Me.ChooseEdgeToolStripMenuItem.Name = "ChooseEdgeToolStripMenuItem"
        Me.ChooseEdgeToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ChooseEdgeToolStripMenuItem.Text = "Edge"
        '
        'ChooseFaceToolStripMenuItem
        '
        Me.ChooseFaceToolStripMenuItem.Name = "ChooseFaceToolStripMenuItem"
        Me.ChooseFaceToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.ChooseFaceToolStripMenuItem.Text = "Face"
        '
        'VertexRingToolStripMenuItem
        '
        Me.VertexRingToolStripMenuItem.Name = "VertexRingToolStripMenuItem"
        Me.VertexRingToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.VertexRingToolStripMenuItem.Text = "VertexRing"
        '
        'EdgeRingToolStripMenuItem
        '
        Me.EdgeRingToolStripMenuItem.Name = "EdgeRingToolStripMenuItem"
        Me.EdgeRingToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.EdgeRingToolStripMenuItem.Text = "EdgeRing"
        '
        'FaceRingToolStripMenuItem
        '
        Me.FaceRingToolStripMenuItem.Name = "FaceRingToolStripMenuItem"
        Me.FaceRingToolStripMenuItem.Size = New System.Drawing.Size(139, 22)
        Me.FaceRingToolStripMenuItem.Text = "FaceRing"
        '
        'ShowToolStripMenuItem
        '
        Me.ShowToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ShowVertexToolStripMenuItem, Me.ShowEdgeToolStripMenuItem, Me.ShowFaceToolStripMenuItem})
        Me.ShowToolStripMenuItem.Name = "ShowToolStripMenuItem"
        Me.ShowToolStripMenuItem.Size = New System.Drawing.Size(66, 21)
        Me.ShowToolStripMenuItem.Text = "Show(&S)"
        '
        'ShowVertexToolStripMenuItem
        '
        Me.ShowVertexToolStripMenuItem.Name = "ShowVertexToolStripMenuItem"
        Me.ShowVertexToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ShowVertexToolStripMenuItem.Text = "Vertex(&V)"
        '
        'ShowEdgeToolStripMenuItem
        '
        Me.ShowEdgeToolStripMenuItem.Name = "ShowEdgeToolStripMenuItem"
        Me.ShowEdgeToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ShowEdgeToolStripMenuItem.Text = "Edge(&E)"
        '
        'ShowFaceToolStripMenuItem
        '
        Me.ShowFaceToolStripMenuItem.Checked = True
        Me.ShowFaceToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked
        Me.ShowFaceToolStripMenuItem.Name = "ShowFaceToolStripMenuItem"
        Me.ShowFaceToolStripMenuItem.Size = New System.Drawing.Size(152, 22)
        Me.ShowFaceToolStripMenuItem.Text = "Face(&F)"
        '
        'CameraToolStripMenuItem
        '
        Me.CameraToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ResetToolStripMenuItem})
        Me.CameraToolStripMenuItem.Name = "CameraToolStripMenuItem"
        Me.CameraToolStripMenuItem.Size = New System.Drawing.Size(65, 21)
        Me.CameraToolStripMenuItem.Text = "Camera"
        '
        'ResetToolStripMenuItem
        '
        Me.ResetToolStripMenuItem.Name = "ResetToolStripMenuItem"
        Me.ResetToolStripMenuItem.Size = New System.Drawing.Size(108, 22)
        Me.ResetToolStripMenuItem.Text = "Reset"
        '
        'PictureBox
        '
        Me.PictureBox.Dock = System.Windows.Forms.DockStyle.Fill
        Me.PictureBox.Location = New System.Drawing.Point(0, 25)
        Me.PictureBox.Name = "PictureBox"
        Me.PictureBox.Size = New System.Drawing.Size(667, 362)
        Me.PictureBox.TabIndex = 1
        Me.PictureBox.TabStop = False
        '
        'OpenMeshFileDialog
        '
        Me.OpenMeshFileDialog.Filter = "obj 模型|*.obj"
        '
        'SaveMeshFileDialog
        '
        Me.SaveMeshFileDialog.Filter = "obj 模型|*.obj"
        '
        'RenderTimer
        '
        Me.RenderTimer.Interval = 50
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(667, 387)
        Me.Controls.Add(Me.PictureBox)
        Me.Controls.Add(Me.MenuStrip1)
        Me.KeyPreview = True
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "Form1"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        CType(Me.PictureBox, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub
    Friend WithEvents MenuStrip1 As System.Windows.Forms.MenuStrip
    Friend WithEvents FileToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents OpenToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SaveToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ChooseToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ChoosePointToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ChooseVertexToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ChooseFaceToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ShowToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ShowVertexToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ShowEdgeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ShowFaceToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CameraToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ResetToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents PictureBox As System.Windows.Forms.PictureBox
    Friend WithEvents OpenMeshFileDialog As System.Windows.Forms.OpenFileDialog
    Friend WithEvents SaveMeshFileDialog As System.Windows.Forms.SaveFileDialog
    Friend WithEvents ChooseEdgeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents VertexRingToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents EdgeRingToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents FaceRingToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RenderTimer As System.Windows.Forms.Timer

End Class
