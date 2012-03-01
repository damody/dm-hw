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
        Me.ImplicitSmoothToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChoosePointToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseVertexToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseEdgeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ChooseFaceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.DeleteEdgeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.DontMoveToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.SkeletonNodeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.RingToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.RingVertexToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.RingEdgeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.RingFaceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowVertexToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowEdgeToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ShowFaceToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.CameraToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.VertexesToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.EdgesToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.FacesToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ViewerToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ViewerUpdateToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.ResetToolStripMenuItem = New System.Windows.Forms.ToolStripMenuItem
        Me.PictureBox_DrawOSG = New System.Windows.Forms.PictureBox
        Me.OpenMeshFileDialog = New System.Windows.Forms.OpenFileDialog
        Me.SaveMeshFileDialog = New System.Windows.Forms.SaveFileDialog
        Me.EdgeTrackBar = New System.Windows.Forms.TrackBar
        Me.StatusStrip1 = New System.Windows.Forms.StatusStrip
        Me.MeshReduce = New System.Windows.Forms.Timer(Me.components)
        Me.Button1 = New System.Windows.Forms.Button
        Me.Button2 = New System.Windows.Forms.Button
        Me.Label1 = New System.Windows.Forms.Label
        Me.CheckBox_Convex = New System.Windows.Forms.CheckBox
        Me.TrackBar_Transparency = New System.Windows.Forms.TrackBar
        Me.Label_Face_Transparency = New System.Windows.Forms.Label
        Me.ContextMenuStrip_RClick = New System.Windows.Forms.ContextMenuStrip(Me.components)
        Me.ToolStripMenuItem2 = New System.Windows.Forms.ToolStripMenuItem
        Me.MenuStrip1.SuspendLayout()
        CType(Me.PictureBox_DrawOSG, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.EdgeTrackBar, System.ComponentModel.ISupportInitialize).BeginInit()
        CType(Me.TrackBar_Transparency, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.ContextMenuStrip_RClick.SuspendLayout()
        Me.SuspendLayout()
        '
        'MenuStrip1
        '
        Me.MenuStrip1.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.FileToolStripMenuItem, Me.ChooseToolStripMenuItem, Me.RingToolStripMenuItem, Me.ShowToolStripMenuItem, Me.CameraToolStripMenuItem, Me.ViewerToolStripMenuItem})
        Me.MenuStrip1.Location = New System.Drawing.Point(0, 0)
        Me.MenuStrip1.Name = "MenuStrip1"
        Me.MenuStrip1.Size = New System.Drawing.Size(667, 24)
        Me.MenuStrip1.TabIndex = 0
        Me.MenuStrip1.Text = "MenuStrip1"
        '
        'FileToolStripMenuItem
        '
        Me.FileToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.OpenToolStripMenuItem, Me.SaveToolStripMenuItem, Me.ImplicitSmoothToolStripMenuItem})
        Me.FileToolStripMenuItem.Name = "FileToolStripMenuItem"
        Me.FileToolStripMenuItem.Size = New System.Drawing.Size(39, 20)
        Me.FileToolStripMenuItem.Text = "File"
        '
        'OpenToolStripMenuItem
        '
        Me.OpenToolStripMenuItem.Name = "OpenToolStripMenuItem"
        Me.OpenToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.OpenToolStripMenuItem.Text = "Open"
        '
        'SaveToolStripMenuItem
        '
        Me.SaveToolStripMenuItem.Name = "SaveToolStripMenuItem"
        Me.SaveToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.SaveToolStripMenuItem.Text = "Save"
        '
        'ImplicitSmoothToolStripMenuItem
        '
        Me.ImplicitSmoothToolStripMenuItem.Name = "ImplicitSmoothToolStripMenuItem"
        Me.ImplicitSmoothToolStripMenuItem.Size = New System.Drawing.Size(162, 22)
        Me.ImplicitSmoothToolStripMenuItem.Text = "ImplicitSmooth"
        '
        'ChooseToolStripMenuItem
        '
        Me.ChooseToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ChoosePointToolStripMenuItem, Me.ChooseVertexToolStripMenuItem, Me.ChooseEdgeToolStripMenuItem, Me.ChooseFaceToolStripMenuItem, Me.DeleteEdgeToolStripMenuItem, Me.DontMoveToolStripMenuItem, Me.SkeletonNodeToolStripMenuItem})
        Me.ChooseToolStripMenuItem.Name = "ChooseToolStripMenuItem"
        Me.ChooseToolStripMenuItem.Size = New System.Drawing.Size(63, 20)
        Me.ChooseToolStripMenuItem.Text = "Choose"
        '
        'ChoosePointToolStripMenuItem
        '
        Me.ChoosePointToolStripMenuItem.Name = "ChoosePointToolStripMenuItem"
        Me.ChoosePointToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.ChoosePointToolStripMenuItem.Text = "Point"
        '
        'ChooseVertexToolStripMenuItem
        '
        Me.ChooseVertexToolStripMenuItem.Name = "ChooseVertexToolStripMenuItem"
        Me.ChooseVertexToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.ChooseVertexToolStripMenuItem.Text = "Vertex"
        '
        'ChooseEdgeToolStripMenuItem
        '
        Me.ChooseEdgeToolStripMenuItem.Name = "ChooseEdgeToolStripMenuItem"
        Me.ChooseEdgeToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.ChooseEdgeToolStripMenuItem.Text = "Edge"
        '
        'ChooseFaceToolStripMenuItem
        '
        Me.ChooseFaceToolStripMenuItem.Name = "ChooseFaceToolStripMenuItem"
        Me.ChooseFaceToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.ChooseFaceToolStripMenuItem.Text = "Face"
        '
        'DeleteEdgeToolStripMenuItem
        '
        Me.DeleteEdgeToolStripMenuItem.Name = "DeleteEdgeToolStripMenuItem"
        Me.DeleteEdgeToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.DeleteEdgeToolStripMenuItem.Text = "DeleteEdge"
        '
        'DontMoveToolStripMenuItem
        '
        Me.DontMoveToolStripMenuItem.Name = "DontMoveToolStripMenuItem"
        Me.DontMoveToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.DontMoveToolStripMenuItem.Text = "DontMove"
        '
        'SkeletonNodeToolStripMenuItem
        '
        Me.SkeletonNodeToolStripMenuItem.Name = "SkeletonNodeToolStripMenuItem"
        Me.SkeletonNodeToolStripMenuItem.Size = New System.Drawing.Size(158, 22)
        Me.SkeletonNodeToolStripMenuItem.Text = "SkeletonNode"
        '
        'RingToolStripMenuItem
        '
        Me.RingToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.RingVertexToolStripMenuItem, Me.RingEdgeToolStripMenuItem, Me.RingFaceToolStripMenuItem})
        Me.RingToolStripMenuItem.Name = "RingToolStripMenuItem"
        Me.RingToolStripMenuItem.Size = New System.Drawing.Size(46, 20)
        Me.RingToolStripMenuItem.Text = "Ring"
        '
        'RingVertexToolStripMenuItem
        '
        Me.RingVertexToolStripMenuItem.Name = "RingVertexToolStripMenuItem"
        Me.RingVertexToolStripMenuItem.Size = New System.Drawing.Size(112, 22)
        Me.RingVertexToolStripMenuItem.Text = "Vertex"
        '
        'RingEdgeToolStripMenuItem
        '
        Me.RingEdgeToolStripMenuItem.Name = "RingEdgeToolStripMenuItem"
        Me.RingEdgeToolStripMenuItem.Size = New System.Drawing.Size(112, 22)
        Me.RingEdgeToolStripMenuItem.Text = "Edge"
        '
        'RingFaceToolStripMenuItem
        '
        Me.RingFaceToolStripMenuItem.Name = "RingFaceToolStripMenuItem"
        Me.RingFaceToolStripMenuItem.Size = New System.Drawing.Size(112, 22)
        Me.RingFaceToolStripMenuItem.Text = "Face"
        '
        'ShowToolStripMenuItem
        '
        Me.ShowToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ShowVertexToolStripMenuItem, Me.ShowEdgeToolStripMenuItem, Me.ShowFaceToolStripMenuItem})
        Me.ShowToolStripMenuItem.Name = "ShowToolStripMenuItem"
        Me.ShowToolStripMenuItem.Size = New System.Drawing.Size(66, 20)
        Me.ShowToolStripMenuItem.Text = "Show(&S)"
        '
        'ShowVertexToolStripMenuItem
        '
        Me.ShowVertexToolStripMenuItem.Name = "ShowVertexToolStripMenuItem"
        Me.ShowVertexToolStripMenuItem.Size = New System.Drawing.Size(128, 22)
        Me.ShowVertexToolStripMenuItem.Text = "Vertex(&V)"
        '
        'ShowEdgeToolStripMenuItem
        '
        Me.ShowEdgeToolStripMenuItem.Name = "ShowEdgeToolStripMenuItem"
        Me.ShowEdgeToolStripMenuItem.Size = New System.Drawing.Size(128, 22)
        Me.ShowEdgeToolStripMenuItem.Text = "Edge(&E)"
        '
        'ShowFaceToolStripMenuItem
        '
        Me.ShowFaceToolStripMenuItem.Checked = True
        Me.ShowFaceToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked
        Me.ShowFaceToolStripMenuItem.Name = "ShowFaceToolStripMenuItem"
        Me.ShowFaceToolStripMenuItem.Size = New System.Drawing.Size(128, 22)
        Me.ShowFaceToolStripMenuItem.Text = "Face(&F)"
        '
        'CameraToolStripMenuItem
        '
        Me.CameraToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.VertexesToolStripMenuItem, Me.EdgesToolStripMenuItem, Me.FacesToolStripMenuItem})
        Me.CameraToolStripMenuItem.Name = "CameraToolStripMenuItem"
        Me.CameraToolStripMenuItem.Size = New System.Drawing.Size(65, 20)
        Me.CameraToolStripMenuItem.Text = "Clear(&C)"
        '
        'VertexesToolStripMenuItem
        '
        Me.VertexesToolStripMenuItem.Name = "VertexesToolStripMenuItem"
        Me.VertexesToolStripMenuItem.Size = New System.Drawing.Size(124, 22)
        Me.VertexesToolStripMenuItem.Text = "Vertexes"
        '
        'EdgesToolStripMenuItem
        '
        Me.EdgesToolStripMenuItem.Name = "EdgesToolStripMenuItem"
        Me.EdgesToolStripMenuItem.Size = New System.Drawing.Size(124, 22)
        Me.EdgesToolStripMenuItem.Text = "Edges"
        '
        'FacesToolStripMenuItem
        '
        Me.FacesToolStripMenuItem.Name = "FacesToolStripMenuItem"
        Me.FacesToolStripMenuItem.Size = New System.Drawing.Size(124, 22)
        Me.FacesToolStripMenuItem.Text = "Faces"
        '
        'ViewerToolStripMenuItem
        '
        Me.ViewerToolStripMenuItem.DropDownItems.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ViewerUpdateToolStripMenuItem, Me.ResetToolStripMenuItem})
        Me.ViewerToolStripMenuItem.Name = "ViewerToolStripMenuItem"
        Me.ViewerToolStripMenuItem.Size = New System.Drawing.Size(58, 20)
        Me.ViewerToolStripMenuItem.Text = "Viewer"
        '
        'ViewerUpdateToolStripMenuItem
        '
        Me.ViewerUpdateToolStripMenuItem.Checked = True
        Me.ViewerUpdateToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked
        Me.ViewerUpdateToolStripMenuItem.Name = "ViewerUpdateToolStripMenuItem"
        Me.ViewerUpdateToolStripMenuItem.Size = New System.Drawing.Size(119, 22)
        Me.ViewerUpdateToolStripMenuItem.Text = "Update"
        '
        'ResetToolStripMenuItem
        '
        Me.ResetToolStripMenuItem.Name = "ResetToolStripMenuItem"
        Me.ResetToolStripMenuItem.Size = New System.Drawing.Size(119, 22)
        Me.ResetToolStripMenuItem.Text = "Reset"
        '
        'PictureBox_DrawOSG
        '
        Me.PictureBox_DrawOSG.Dock = System.Windows.Forms.DockStyle.Fill
        Me.PictureBox_DrawOSG.Location = New System.Drawing.Point(0, 24)
        Me.PictureBox_DrawOSG.Name = "PictureBox_DrawOSG"
        Me.PictureBox_DrawOSG.Size = New System.Drawing.Size(667, 363)
        Me.PictureBox_DrawOSG.TabIndex = 1
        Me.PictureBox_DrawOSG.TabStop = False
        '
        'OpenMeshFileDialog
        '
        Me.OpenMeshFileDialog.Filter = "obj 模型|*.obj"
        '
        'SaveMeshFileDialog
        '
        Me.SaveMeshFileDialog.Filter = "obj 模型|*.obj"
        '
        'EdgeTrackBar
        '
        Me.EdgeTrackBar.Location = New System.Drawing.Point(457, 376)
        Me.EdgeTrackBar.Maximum = 1000
        Me.EdgeTrackBar.Minimum = 1
        Me.EdgeTrackBar.Name = "EdgeTrackBar"
        Me.EdgeTrackBar.Size = New System.Drawing.Size(176, 45)
        Me.EdgeTrackBar.TabIndex = 2
        Me.EdgeTrackBar.Value = 1
        '
        'StatusStrip1
        '
        Me.StatusStrip1.Location = New System.Drawing.Point(0, 365)
        Me.StatusStrip1.Name = "StatusStrip1"
        Me.StatusStrip1.Size = New System.Drawing.Size(667, 22)
        Me.StatusStrip1.TabIndex = 3
        Me.StatusStrip1.Text = "StatusStrip1"
        '
        'MeshReduce
        '
        '
        'Button1
        '
        Me.Button1.Location = New System.Drawing.Point(353, 0)
        Me.Button1.Margin = New System.Windows.Forms.Padding(2)
        Me.Button1.Name = "Button1"
        Me.Button1.Size = New System.Drawing.Size(70, 22)
        Me.Button1.TabIndex = 4
        Me.Button1.Text = "開始減面"
        Me.Button1.UseVisualStyleBackColor = True
        '
        'Button2
        '
        Me.Button2.Location = New System.Drawing.Point(428, 0)
        Me.Button2.Margin = New System.Windows.Forms.Padding(2)
        Me.Button2.Name = "Button2"
        Me.Button2.Size = New System.Drawing.Size(70, 22)
        Me.Button2.TabIndex = 5
        Me.Button2.Text = "停止減面"
        Me.Button2.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(394, 373)
        Me.Label1.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(11, 12)
        Me.Label1.TabIndex = 6
        Me.Label1.Text = "1"
        '
        'CheckBox_Convex
        '
        Me.CheckBox_Convex.AutoSize = True
        Me.CheckBox_Convex.Location = New System.Drawing.Point(502, 4)
        Me.CheckBox_Convex.Margin = New System.Windows.Forms.Padding(2)
        Me.CheckBox_Convex.Name = "CheckBox_Convex"
        Me.CheckBox_Convex.Size = New System.Drawing.Size(94, 16)
        Me.CheckBox_Convex.TabIndex = 7
        Me.CheckBox_Convex.Text = "Convex Check"
        Me.CheckBox_Convex.UseVisualStyleBackColor = True
        '
        'TrackBar_Transparency
        '
        Me.TrackBar_Transparency.Location = New System.Drawing.Point(92, 373)
        Me.TrackBar_Transparency.Maximum = 100
        Me.TrackBar_Transparency.Name = "TrackBar_Transparency"
        Me.TrackBar_Transparency.Size = New System.Drawing.Size(91, 45)
        Me.TrackBar_Transparency.TabIndex = 8
        Me.TrackBar_Transparency.Value = 100
        '
        'Label_Face_Transparency
        '
        Me.Label_Face_Transparency.AutoSize = True
        Me.Label_Face_Transparency.Location = New System.Drawing.Point(9, 373)
        Me.Label_Face_Transparency.Margin = New System.Windows.Forms.Padding(2, 0, 2, 0)
        Me.Label_Face_Transparency.Name = "Label_Face_Transparency"
        Me.Label_Face_Transparency.Size = New System.Drawing.Size(92, 12)
        Me.Label_Face_Transparency.TabIndex = 9
        Me.Label_Face_Transparency.Text = "Face Transparency"
        '
        'ContextMenuStrip_RClick
        '
        Me.ContextMenuStrip_RClick.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Me.ToolStripMenuItem2})
        Me.ContextMenuStrip_RClick.Name = "ContextMenuStrip1"
        Me.ContextMenuStrip_RClick.Size = New System.Drawing.Size(98, 26)
        '
        'ToolStripMenuItem2
        '
        Me.ToolStripMenuItem2.Name = "ToolStripMenuItem2"
        Me.ToolStripMenuItem2.Size = New System.Drawing.Size(97, 22)
        Me.ToolStripMenuItem2.Text = "123"
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(667, 387)
        Me.Controls.Add(Me.Label_Face_Transparency)
        Me.Controls.Add(Me.TrackBar_Transparency)
        Me.Controls.Add(Me.Label1)
        Me.Controls.Add(Me.CheckBox_Convex)
        Me.Controls.Add(Me.Button2)
        Me.Controls.Add(Me.Button1)
        Me.Controls.Add(Me.EdgeTrackBar)
        Me.Controls.Add(Me.StatusStrip1)
        Me.Controls.Add(Me.PictureBox_DrawOSG)
        Me.Controls.Add(Me.MenuStrip1)
        Me.KeyPreview = True
        Me.MainMenuStrip = Me.MenuStrip1
        Me.Name = "Form1"
        Me.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen
        Me.Text = "I am Visual Basic!"
        Me.MenuStrip1.ResumeLayout(False)
        Me.MenuStrip1.PerformLayout()
        CType(Me.PictureBox_DrawOSG, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.EdgeTrackBar, System.ComponentModel.ISupportInitialize).EndInit()
        CType(Me.TrackBar_Transparency, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ContextMenuStrip_RClick.ResumeLayout(False)
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
    Friend WithEvents PictureBox_DrawOSG As System.Windows.Forms.PictureBox
    Friend WithEvents OpenMeshFileDialog As System.Windows.Forms.OpenFileDialog
    Friend WithEvents SaveMeshFileDialog As System.Windows.Forms.SaveFileDialog
    Friend WithEvents ChooseEdgeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RingToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RingVertexToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RingEdgeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents RingFaceToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents VertexesToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents EdgesToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents FacesToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents DeleteEdgeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents EdgeTrackBar As System.Windows.Forms.TrackBar
    Friend WithEvents StatusStrip1 As System.Windows.Forms.StatusStrip
    Friend WithEvents MeshReduce As System.Windows.Forms.Timer
    Friend WithEvents Button1 As System.Windows.Forms.Button
    Friend WithEvents Button2 As System.Windows.Forms.Button
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents DontMoveToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents CheckBox_Convex As System.Windows.Forms.CheckBox
    Friend WithEvents ViewerToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ViewerUpdateToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents SkeletonNodeToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents TrackBar_Transparency As System.Windows.Forms.TrackBar
    Friend WithEvents Label_Face_Transparency As System.Windows.Forms.Label
    Friend WithEvents ContextMenuStrip_RClick As System.Windows.Forms.ContextMenuStrip
    Friend WithEvents ToolStripMenuItem2 As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ResetToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem
    Friend WithEvents ImplicitSmoothToolStripMenuItem As System.Windows.Forms.ToolStripMenuItem

End Class
