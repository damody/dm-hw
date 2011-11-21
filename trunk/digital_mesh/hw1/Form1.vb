Imports digital_meshLib
Imports System.Windows.Forms

Public Class Form1
    Dim osg As New osgControl

    Private Sub OpenToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles OpenToolStripMenuItem.Click
        OpenMeshFileDialog.ShowDialog()
    End Sub

    Private Sub SaveToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles SaveToolStripMenuItem.Click

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
    Private Sub PictureBox_MouseDown(ByVal sender As System.Object, ByVal e As System.Windows.Forms.MouseEventArgs) Handles PictureBox.MouseDown
        If ChoosePointToolStripMenuItem.Checked Then
            osg.SelectPoint(PictureBox.Width - e.X, PictureBox.Height - e.Y)
        End If
        If ChooseVertexToolStripMenuItem.Checked Then
            osg.SelectVertex(PictureBox.Width - e.X, PictureBox.Height - e.Y)
        End If
        If ChooseEdgeToolStripMenuItem.Checked Then
            osg.SelectEdge(PictureBox.Width - e.X, PictureBox.Height - e.Y)
        End If
        If ChooseFaceToolStripMenuItem.Checked Then
            osg.SelectFace(PictureBox.Width - e.X, PictureBox.Height - e.Y)
        End If
        If VertexRingToolStripMenuItem.Checked Then
            osg.SelectVertexRing(PictureBox.Width - e.X, PictureBox.Height - e.Y)
        End If
        If EdgeRingToolStripMenuItem.Checked Then
            osg.SelectEdgeRing(PictureBox.Width - e.X, PictureBox.Height - e.Y)
        End If
        If FaceRingToolStripMenuItem.Checked Then
            osg.SelectFaceRing(PictureBox.Width - e.X, PictureBox.Height - e.Y)
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

    Private Sub ResetToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles ResetToolStripMenuItem.Click

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

    Private Sub VertexRingToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles VertexRingToolStripMenuItem.Click
        VertexRingToolStripMenuItem.Checked = Not (VertexRingToolStripMenuItem.Checked)
    End Sub

    Private Sub EdgeRingToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles EdgeRingToolStripMenuItem.Click
        EdgeRingToolStripMenuItem.Checked = Not (EdgeRingToolStripMenuItem.Checked)
    End Sub

    Private Sub FaceRingToolStripMenuItem_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles FaceRingToolStripMenuItem.Click
        FaceRingToolStripMenuItem.Checked = Not (FaceRingToolStripMenuItem.Checked)
    End Sub

    Private Sub RenderTimer_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles RenderTimer.Tick
        'osg.Render()
    End Sub

    Private Sub Form1_KeyPress(ByVal sender As System.Object, ByVal e As System.Windows.Forms.KeyPressEventArgs) Handles MyBase.KeyPress
        If e.KeyChar = "q" Or e.KeyChar = "Q" Then
            ShowVertexToolStripMenuItem.Checked = Not (ShowVertexToolStripMenuItem.Checked)
            If ShowVertexToolStripMenuItem.Checked Then
                osg.ShowVertex()
            Else
                osg.HideVertex()
            End If
        End If
        If e.KeyChar = "w" Or e.KeyChar = "W" Then
            ShowEdgeToolStripMenuItem.Checked = Not (ShowEdgeToolStripMenuItem.Checked)
            If ShowEdgeToolStripMenuItem.Checked Then
                osg.ShowEdge()
            Else
                osg.HideEdge()
            End If
        End If
        If e.KeyChar = "e" Or e.KeyChar = "E" Then
            ShowFaceToolStripMenuItem.Checked = Not (ShowFaceToolStripMenuItem.Checked)
            If ShowFaceToolStripMenuItem.Checked Then
                osg.ShowFace()
            Else
                osg.HideFace()
            End If
        End If
    End Sub
End Class
