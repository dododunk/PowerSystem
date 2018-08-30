using System;
using System.ComponentModel;
using System.Drawing;
using System.Security.Permissions;
namespace System.Windows.Forms
{
	public abstract class SkinFormRenderer
	{
		private EventHandlerList _events;
		private static readonly object EventRenderSkinFormCaption = new object();
		private static readonly object EventRenderSkinFormBorder = new object();
		private static readonly object EventRenderSkinFormBackground = new object();
		private static readonly object EventRenderSkinFormControlBox = new object();
		public event SkinFormCaptionRenderEventHandler RenderSkinFormCaption
		{
			add
			{
				this.AddHandler(SkinFormRenderer.EventRenderSkinFormCaption, value);
			}
			remove
			{
				this.RemoveHandler(SkinFormRenderer.EventRenderSkinFormCaption, value);
			}
		}
		public event SkinFormBorderRenderEventHandler RenderSkinFormBorder
		{
			add
			{
				this.AddHandler(SkinFormRenderer.EventRenderSkinFormBorder, value);
			}
			remove
			{
				this.RemoveHandler(SkinFormRenderer.EventRenderSkinFormBorder, value);
			}
		}
		public event SkinFormBackgroundRenderEventHandler RenderSkinFormBackground
		{
			add
			{
				this.AddHandler(SkinFormRenderer.EventRenderSkinFormBackground, value);
			}
			remove
			{
				this.RemoveHandler(SkinFormRenderer.EventRenderSkinFormBackground, value);
			}
		}
		public event SkinFormControlBoxRenderEventHandler RenderSkinFormControlBox
		{
			add
			{
				this.AddHandler(SkinFormRenderer.EventRenderSkinFormControlBox, value);
			}
			remove
			{
				this.RemoveHandler(SkinFormRenderer.EventRenderSkinFormControlBox, value);
			}
		}
		protected EventHandlerList Events
		{
			get
			{
				if (this._events == null)
				{
					this._events = new EventHandlerList();
				}
				return this._events;
			}
		}
		public abstract Region CreateRegion(SkinForm form);
		public abstract void InitSkinForm(SkinForm form);
		public void DrawSkinFormCaption(SkinFormCaptionRenderEventArgs e)
		{
			this.OnRenderSkinFormCaption(e);
			SkinFormCaptionRenderEventHandler skinFormCaptionRenderEventHandler = this.Events[SkinFormRenderer.EventRenderSkinFormCaption] as SkinFormCaptionRenderEventHandler;
			if (skinFormCaptionRenderEventHandler != null)
			{
				skinFormCaptionRenderEventHandler(this, e);
			}
		}
		public void DrawSkinFormBorder(SkinFormBorderRenderEventArgs e)
		{
			this.OnRenderSkinFormBorder(e);
			SkinFormBorderRenderEventHandler skinFormBorderRenderEventHandler = this.Events[SkinFormRenderer.EventRenderSkinFormBorder] as SkinFormBorderRenderEventHandler;
			if (skinFormBorderRenderEventHandler != null)
			{
				skinFormBorderRenderEventHandler(this, e);
			}
		}
		public void DrawSkinFormBackground(SkinFormBackgroundRenderEventArgs e)
		{
			this.OnRenderSkinFormBackground(e);
			SkinFormBackgroundRenderEventHandler skinFormBackgroundRenderEventHandler = this.Events[SkinFormRenderer.EventRenderSkinFormBackground] as SkinFormBackgroundRenderEventHandler;
			if (skinFormBackgroundRenderEventHandler != null)
			{
				skinFormBackgroundRenderEventHandler(this, e);
			}
		}
		public void DrawSkinFormControlBox(SkinFormControlBoxRenderEventArgs e)
		{
			this.OnRenderSkinFormControlBox(e);
			SkinFormControlBoxRenderEventHandler skinFormControlBoxRenderEventHandler = this.Events[SkinFormRenderer.EventRenderSkinFormControlBox] as SkinFormControlBoxRenderEventHandler;
			if (skinFormControlBoxRenderEventHandler != null)
			{
				skinFormControlBoxRenderEventHandler(this, e);
			}
		}
		protected abstract void OnRenderSkinFormCaption(SkinFormCaptionRenderEventArgs e);
		protected abstract void OnRenderSkinFormBorder(SkinFormBorderRenderEventArgs e);
		protected abstract void OnRenderSkinFormBackground(SkinFormBackgroundRenderEventArgs e);
		protected abstract void OnRenderSkinFormControlBox(SkinFormControlBoxRenderEventArgs e);
		[UIPermission(SecurityAction.Demand, Window = UIPermissionWindow.AllWindows)]
		protected void AddHandler(object key, Delegate value)
		{
			this.Events.AddHandler(key, value);
		}
		[UIPermission(SecurityAction.Demand, Window = UIPermissionWindow.AllWindows)]
		protected void RemoveHandler(object key, Delegate value)
		{
			this.Events.RemoveHandler(key, value);
		}
	}
}
