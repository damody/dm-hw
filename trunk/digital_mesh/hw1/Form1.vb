Imports digital_meshLib
Imports System.Windows.Forms

Public Class Form1
    Dim osg As New osgControl

    Private Sub OpenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenToolStripMenuItem.Click
        OpenMeshFileDialog.ShowDialog()
    End Sub

    Private Sub SaveToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveToolStripMenuItem.Click
        SaveMeshFileDialog.ShowDialog()
    End Sub

    Private Sub PictureBox_MouseDown(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox_DrawOSG.MouseDown
        Me.PictureBox_DrawOSG.Focus() 'From trackbar get focus
        Dim x, y As Int32
        x = PictureBox_DrawOSG.Width - e.X
        y = PictureBox_DrawOSG.Height - e.Y
        If e.Button = MouseButtons.Left Then
            If SkeletonNodeToolStripMenuItem.Checked Then
                osg.SelectSkeletonNode(x, y)
            End If
        End If
        If e.Button = MouseButtons.Right Then
            If ChoosePointToolStripMenuItem.Checked Then
                osg.SelectPoint(x, y)
            End If
            If SkeletonNodeToolStripMenuItem.Checked Then
                Dim NumOfNode As Int32 = osg.GetNumOfAllRayTraceNodes(x, y)
                If NumOfNode > 1 Then
                    ContextMenuStrip_RClick.Items.Clear()
                    For index As Integer = 1 To NumOfNode
                        Dim Layer As New System.Windows.Forms.ToolStripMenuItem
                        Layer.Name = "Layer" + Str(index)
                        Layer.Size = New System.Drawing.Size(152, 24)
                        Layer.Text = "Layer" + Str(index)
                        ContextMenuStrip_RClick.Items.AddRange(New System.Windows.Forms.ToolStripItem() {Layer})
                    Next
                    ContextMenuStrip_RClick.Show(Me, e.X, e.Y)
                ElseIf NumOfNode = 1 Then
                    osg.AddLastTraceNodeByIndex(1)
                End If
            End If
            If ChooseVertexToolStripMenuItem.Checked Then
                osg.SelectVertex(x, y)
                If RingVertexToolStripMenuItem.Checked Then
                    osg.SelectVertexRingVertex(x, y)
                End If
                If RingEdgeToolStripMenuItem.Checked Then
                    osg.SelectVertexRingEdge(x, y)
                End If
                If RingFaceToolStripMenuItem.Checked Then
                    osg.SelectVertexRingFace(x, y)
                End If
            End If
            If DontMoveToolStripMenuItem.Checked Then
                osg.SelectDontMoveFace(x, y)
            End If
            If DeleteEdgeToolStripMenuItem.Checked Then
                osg.DeleteSelectEdge(x, y)
            End If
            If ChooseEdgeToolStripMenuItem.Checked Then
                osg.SelectEdge(x, y)
                If RingVertexToolStripMenuItem.Checked Then
                    osg.SelectEdgeRingVertex(x, y)
                End If
                If RingEdgeToolStripMenuItem.Checked Then
                    osg.SelectEdgeRingEdge(x, y)
                End If
                If RingFaceToolStripMenuItem.Checked Then
                    osg.SelectEdgeRingFace(x, y)
                End If
            End If
            If ChooseFaceToolStripMenuItem.Checked Then
                osg.SelectFace(x, y)
                If RingVertexToolStripMenuItem.Checked Then
                    osg.SelectFaceRingVertex(x, y)
                End If
                If RingEdgeToolStripMenuItem.Checked Then
                    osg.SelectFaceRingEdge(x, y)
                End If
                If RingFaceToolStripMenuItem.Checked Then
                    osg.SelectFaceRingFace(x, y)
                End If
            End If
        End If

    End Sub

    Private Sub PictureBox_MouseMove(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox_DrawOSG.MouseMove
        If e.Button = MouseButtons.Right And DontMoveToolStripMenuItem.Checked Then
            osg.SelectDontMoveFace(PictureBox_DrawOSG.Width - e.X, PictureBox_DrawOSG.Height - e.Y)
        End If
    End Sub

    Private Sub PictureBox_MouseUp(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox_DrawOSG.MouseUp
    End Sub
    Private Sub VertexToolStripMenuItem1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ShowVertexToolStripMenuItem.Click
        ShowVertexToolStripMenuItem.Checked = Not (ShowVertexToolStripMenuItem.Checked)
        If ShowVertexToolStripMenuItem.Checked Then
            osg.ShowVertex()
        Else
            osg.HideVertex()
        End If
    End Sub

    Private Sub EdgeToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ShowEdgeToolStripMenuItem.Click
        ShowEdgeToolStripMenuItem.Checked = Not (ShowEdgeToolStripMenuItem.Checked)
        If ShowEdgeToolStripMenuItem.Checked Then
            osg.ShowEdge()
        Else
            osg.HideEdge()
        End If
    End Sub

    Private Sub FaceToolStripMenuItem1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ShowFaceToolStripMenuItem.Click
        ShowFaceToolStripMenuItem.Checked = Not (ShowFaceToolStripMenuItem.Checked)
        If ShowFaceToolStripMenuItem.Checked Then
            osg.ShowFace()
        Else
            osg.HideFace()
        End If
    End Sub

    Private Sub ResetToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)

    End Sub

    Private Sub OpenMeshFileDialog_FileOk(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles OpenMeshFileDialog.FileOk
        If OpenMeshFileDialog.CheckFileExists Then
            osg.LoadObjMesh(OpenMeshFileDialog.FileName)
            osg.ResetCamera()
        End If
        If ShowFaceToolStripMenuItem.Checked Then
            osg.ShowFace()
        Else
            osg.HideFace()
        End If
    End Sub

    Private Sub SaveMeshFileDialog_FileOk(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles SaveMeshFileDialog.FileOk
        If SaveMeshFileDialog.ValidateNames Then
            osg.SaveObjMesh(SaveMeshFileDialog.FileName)
        End If
    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        osg.InitOSG(PictureBox_DrawOSG.Handle)
        EdgeTrackBar.Location = New Size(Me.Width - EdgeTrackBar.Width - 50, Me.Height - EdgeTrackBar.Height - 10)
        Label1.Location = New Size(Me.Width - EdgeTrackBar.Width - 100, Me.Height - EdgeTrackBar.Height - 9)
        TrackBar_Transparency.Location = New Size(120, Me.Height - EdgeTrackBar.Height - 10)
        Label_Face_Transparency.Location = New Size(5, Me.Height - EdgeTrackBar.Height - 9)
    End Sub

    Private Sub Form1_KeyDown(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyEventArgs) Handles MyBase.KeyDown
        'clear all
        Select Case Chr(e.KeyCode)
            Case "c", "C"
                osg.ClearVertexes()
                osg.ClearEdges()
                osg.ClearFaces()
        End Select

        If e.Shift = True Then 'select choose mode
            Select Case Chr(e.KeyCode)
                Case "t", "T"
                    ChoosePointToolStripMenuItem.Checked = Not (ChoosePointToolStripMenuItem.Checked)
                Case "v", "V"
                    ChooseVertexToolStripMenuItem.Checked = Not (ChooseVertexToolStripMenuItem.Checked)
                Case "e", "E"
                    ChooseEdgeToolStripMenuItem.Checked = Not (ChooseEdgeToolStripMenuItem.Checked)
                Case "f", "F"
                    ChooseFaceToolStripMenuItem.Checked = Not (ChooseFaceToolStripMenuItem.Checked)
            End Select

        ElseIf e.Control = True Then  'select ring mode
            Select Case Chr(e.KeyCode)
                Case "v", "V"
                    RingVertexToolStripMenuItem.Checked = Not (RingVertexToolStripMenuItem.Checked)
                Case "e", "E"
                    RingEdgeToolStripMenuItem.Checked = Not (RingEdgeToolStripMenuItem.Checked)
                Case "f", "F"
                    RingFaceToolStripMenuItem.Checked = Not (RingFaceToolStripMenuItem.Checked)
            End Select

        Else 'normal mode
            Select Case Chr(e.KeyCode)
                Case "v", "V"
                    ShowVertexToolStripMenuItem.Checked = Not (ShowVertexToolStripMenuItem.Checked)
                    If ShowVertexToolStripMenuItem.Checked Then
                        osg.ShowVertex()
                    Else
                        osg.HideVertex()
                    End If
                Case "e", "E"
                    ShowEdgeToolStripMenuItem.Checked = Not (ShowEdgeToolStripMenuItem.Checked)
                    If ShowEdgeToolStripMenuItem.Checked Then
                        osg.ShowEdge()
                    Else
                        osg.HideEdge()
                    End If
                Case "f", "F"
                    ShowFaceToolStripMenuItem.Checked = Not (ShowFaceToolStripMenuItem.Checked)
                    If ShowFaceToolStripMenuItem.Checked Then
                        osg.ShowFace()
                    Else
                        osg.HideFace()
                    End If
            End Select
        End If
    End Sub

    Private Sub ChoosePointToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ChoosePointToolStripMenuItem.Click
        ChoosePointToolStripMenuItem.Checked = Not (ChoosePointToolStripMenuItem.Checked)
    End Sub
    Private Sub ChooseVertexToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ChooseVertexToolStripMenuItem.Click
        ChooseVertexToolStripMenuItem.Checked = Not (ChooseVertexToolStripMenuItem.Checked)
    End Sub
    Private Sub ChooseEdgeToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ChooseEdgeToolStripMenuItem.Click
        ChooseEdgeToolStripMenuItem.Checked = Not (ChooseEdgeToolStripMenuItem.Checked)
    End Sub
    Private Sub ChooseFaceToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ChooseFaceToolStripMenuItem.Click
        ChooseFaceToolStripMenuItem.Checked = Not (ChooseFaceToolStripMenuItem.Checked)
    End Sub
    Private Sub DontMoveToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles DontMoveToolStripMenuItem.Click
        DontMoveToolStripMenuItem.Checked = Not (DontMoveToolStripMenuItem.Checked)
    End Sub
    Private Sub SkeletonNodeToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SkeletonNodeToolStripMenuItem.Click
        SkeletonNodeToolStripMenuItem.Checked = Not (SkeletonNodeToolStripMenuItem.Checked)
    End Sub

    Private Sub RingVertexToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RingVertexToolStripMenuItem.Click
        RingVertexToolStripMenuItem.Checked = Not (RingVertexToolStripMenuItem.Checked)
    End Sub
    Private Sub RingEdgeToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RingEdgeToolStripMenuItem.Click
        RingEdgeToolStripMenuItem.Checked = Not (RingEdgeToolStripMenuItem.Checked)
    End Sub
    Private Sub RingFaceToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RingFaceToolStripMenuItem.Click
        RingFaceToolStripMenuItem.Checked = Not (RingFaceToolStripMenuItem.Checked)
    End Sub

    Private Sub PointsToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)

    End Sub

    Private Sub VertexesToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles VertexesToolStripMenuItem.Click
        osg.ClearVertexes()
    End Sub

    Private Sub EdgesToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles EdgesToolStripMenuItem.Click
        osg.ClearEdges()
    End Sub

    Private Sub FacesToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FacesToolStripMenuItem.Click
        osg.ClearFaces()
    End Sub

    Private Sub DeleteEdgeToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles DeleteEdgeToolStripMenuItem.Click
        DeleteEdgeToolStripMenuItem.Checked = Not (DeleteEdgeToolStripMenuItem.Checked)
    End Sub

    Private Sub Form1_Resize(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Resize
        EdgeTrackBar.Location = New Size(Me.Width - EdgeTrackBar.Width - 50, Me.Height - EdgeTrackBar.Height - 10)
        Label1.Location = New Size(Me.Width - EdgeTrackBar.Width - 100, Me.Height - EdgeTrackBar.Height - 9)
        TrackBar_Transparency.Location = New Size(120, Me.Height - EdgeTrackBar.Height - 10)
        Label_Face_Transparency.Location = New Size(5, Me.Height - EdgeTrackBar.Height - 9)
    End Sub

    Private Sub EdgeTrackBar_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles EdgeTrackBar.Scroll
        Label1.Text = Str(EdgeTrackBar.Value)
    End Sub

    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        MeshReduce.Enabled = True
    End Sub

    Private Sub Button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button2.Click
        MeshReduce.Enabled = False
    End Sub

    Private Sub MeshReduce_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MeshReduce.Tick
        osg.MeshSimplification(EdgeTrackBar.Value, CheckBox_Convex.Checked)
    End Sub

    Private Sub StopUpdateToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ViewerUpdateToolStripMenuItem.Click
        ViewerUpdateToolStripMenuItem.Checked = Not (ViewerUpdateToolStripMenuItem.Checked)
        osg.SetViewer(ViewerUpdateToolStripMenuItem.Checked)
    End Sub


    Private Sub TrackBar_Transparency_Scroll(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles TrackBar_Transparency.Scroll
        osg.SetFaceTransparency(TrackBar_Transparency.Value)
    End Sub

    Private Sub ContextMenuStrip_RClick_Click(ByVal sender As System.Object, ByVal e As System.Windows.Forms.ToolStripItemClickedEventArgs) Handles ContextMenuStrip_RClick.ItemClicked
        ContextMenuStrip_RClick.Hide()
        Dim cms As System.Windows.Forms.ContextMenuStrip
        cms = TryCast(sender, System.Windows.Forms.ContextMenuStrip)
        If cms IsNot Nothing Then
            For index As Integer = 1 To 10
                If e.ClickedItem.Text = ("Layer" + Str(index)) Then
                    osg.AddLastTraceNodeByIndex(index)
                End If
            Next
        End If
    End Sub

    Private Sub ResetToolStripMenuItem_Click_1(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ResetToolStripMenuItem.Click
        osg.ResetCamera()
    End Sub

    Private Sub ImplicitSmoothToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ImplicitSmoothToolStripMenuItem.Click
        osg.ImplicitSmooth()
    End Sub

    Private Sub ShowSkeletonToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ShowSkeletonToolStripMenuItem.Click
        osg.ShowSmoothSkeleton()
    End Sub
End Class
