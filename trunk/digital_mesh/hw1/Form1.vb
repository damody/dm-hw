Imports digital_meshLib
Imports System.Windows.Forms

Public Class Form1
    Dim osg As New osgControl

    Private Sub OpenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenToolStripMenuItem.Click
        OpenMeshFileDialog.ShowDialog()
    End Sub

    Private Sub SaveToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveToolStripMenuItem.Click

    End Sub

    Private Sub PictureBox_MouseDown(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox.MouseDown
        If e.Button = MouseButtons.Right Then
            If ChoosePointToolStripMenuItem.Checked Then
                osg.SelectPoint(PictureBox.Width - e.X, PictureBox.Height - e.Y)
            End If
            If ChooseVertexToolStripMenuItem.Checked Then
                osg.SelectVertex(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                If RingVertexToolStripMenuItem.Checked Then
                    osg.SelectVertexRingVertex(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
                If RingEdgeToolStripMenuItem.Checked Then
                    osg.SelectVertexRingEdge(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
                If RingFaceToolStripMenuItem.Checked Then
                    osg.SelectVertexRingFace(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
            End If
            If DontMoveToolStripMenuItem.Checked Then
                osg.SelectDontMoveFace(PictureBox.Width - e.X, PictureBox.Height - e.Y)
            End If
            If DeleteEdgeToolStripMenuItem.Checked Then
                osg.DeleteSelectEdge(PictureBox.Width - e.X, PictureBox.Height - e.Y)
            End If
            If ChooseEdgeToolStripMenuItem.Checked Then
                osg.SelectEdge(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                If RingVertexToolStripMenuItem.Checked Then
                    osg.SelectEdgeRingVertex(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
                If RingEdgeToolStripMenuItem.Checked Then
                    osg.SelectEdgeRingEdge(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
                If RingFaceToolStripMenuItem.Checked Then
                    osg.SelectEdgeRingFace(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
            End If
            If ChooseFaceToolStripMenuItem.Checked Then
                osg.SelectFace(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                If RingVertexToolStripMenuItem.Checked Then
                    osg.SelectFaceRingVertex(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
                If RingEdgeToolStripMenuItem.Checked Then
                    osg.SelectFaceRingEdge(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
                If RingFaceToolStripMenuItem.Checked Then
                    osg.SelectFaceRingFace(PictureBox.Width - e.X, PictureBox.Height - e.Y)
                End If
            End If
        End If
    End Sub

    Private Sub PictureBox_MouseMove(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox.MouseMove
    End Sub

    Private Sub PictureBox_MouseUp(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox.MouseUp
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
        End If
        If ShowFaceToolStripMenuItem.Checked Then
            osg.ShowFace()
        Else
            osg.HideFace()
        End If
    End Sub

    Private Sub SaveMeshFileDialog_FileOk(ByVal sender As System.Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles SaveMeshFileDialog.FileOk

    End Sub

    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        osg.InitOSG(PictureBox.Handle)
    End Sub

    Private Sub RenderTimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs)
        'osg.Render()
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
        osg.MeshSimplification(EdgeTrackBar.Value)
    End Sub

   
End Class
