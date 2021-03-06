// Generated by gtkmmproc -- DO NOT MODIFY!


#include <goocanvasmm/tablemodel.h>
#include <goocanvasmm/private/tablemodel_p.h>

/* Copyright (C) 1998-2006 The gtkmm Development Team
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#include <goocanvastable.h>


namespace Goocanvas
{

void TableModel::attach(const Glib::RefPtr<ItemModel>& item, guint left_attach, guint right_attach, guint top_attach, guint bottom_attach, Gtk::AttachOptions xoptions, Gtk::AttachOptions yoptions, double left_padding, double right_padding, double top_padding, double bottom_padding)
{
  const gboolean x_expand = (xoptions & Gtk::EXPAND) != 0;
  const gboolean x_fill = (xoptions & Gtk::FILL) != 0;
  const gboolean x_shrink = (xoptions & Gtk::SHRINK) != 0;
  const gboolean y_expand = (yoptions & Gtk::EXPAND) != 0;
  const gboolean y_fill = (yoptions & Gtk::FILL) != 0;
  const gboolean y_shrink = (yoptions & Gtk::SHRINK) != 0;

  add_child(item);
  goo_canvas_item_model_set_child_properties(GOO_CANVAS_ITEM_MODEL(gobj()), item->gobj(),
                                             "column", left_attach,
                                             "columns", right_attach - left_attach,
                                             "row", top_attach,
                                             "rows", bottom_attach - top_attach,
                                             "x-fill", x_fill,
                                             "x-expand", x_expand,
                                             "x-shrink", x_shrink,
                                             "y-fill", y_fill,
                                             "y-expand", y_expand,
                                             "y-shrink", y_shrink,
                                             "left-padding", left_padding,
                                             "right-padding", right_padding,
                                             "top-padding", top_padding,
                                             "bottom-padding", bottom_padding,
                                              static_cast<void*>(0));
}

void TableModel::set_align(const Glib::RefPtr<ItemModel>& child, double xalign, double yalign)
{
  goo_canvas_item_model_set_child_properties(GOO_CANVAS_ITEM_MODEL(gobj()), child->gobj(),
                                            "xalign", xalign,
                                            "yalign", yalign,
                                            static_cast<void*>(0));
}

void TableModel::set_align(const Glib::RefPtr<ItemModel>& child, Gtk::AlignmentEnum xalign, Gtk::AlignmentEnum yalign)
{
  set_align(child, _gtkmm_align_float_from_enum(xalign), _gtkmm_align_float_from_enum(yalign));
}

} //namspace Goocanvas


namespace
{
} // anonymous namespace


namespace Glib
{

Glib::RefPtr<Goocanvas::TableModel> wrap(GooCanvasTableModel* object, bool take_copy)
{
  return Glib::RefPtr<Goocanvas::TableModel>( dynamic_cast<Goocanvas::TableModel*> (Glib::wrap_auto ((GObject*)(object), take_copy)) );
  //We use dynamic_cast<> in case of multiple inheritance.
}

} /* namespace Glib */


namespace Goocanvas
{


/* The *_Class implementation: */

const Glib::Class& TableModel_Class::init()
{
  if(!gtype_) // create the GType if necessary
  {
    // Glib::Class has to know the class init function to clone custom types.
    class_init_func_ = &TableModel_Class::class_init_function;

    // This is actually just optimized away, apparently with no harm.
    // Make sure that the parent type has been created.
    //CppClassParent::CppObjectType::get_type();

    // Create the wrapper type, with the same class/instance size as the base type.
    register_derived_type(goo_canvas_table_model_get_type());

    // Add derived versions of interfaces, if the C type implements any interfaces:

  }

  return *this;
}


void TableModel_Class::class_init_function(void* g_class, void* class_data)
{
  BaseClassType *const klass = static_cast<BaseClassType*>(g_class);
  CppClassParent::class_init_function(klass, class_data);


}


Glib::ObjectBase* TableModel_Class::wrap_new(GObject* object)
{
  return new TableModel((GooCanvasTableModel*)object);
}


/* The implementation: */

GooCanvasTableModel* TableModel::gobj_copy()
{
  reference();
  return gobj();
}

TableModel::TableModel(const Glib::ConstructParams& construct_params)
:
  Goocanvas::GroupModel(construct_params)
{

}

TableModel::TableModel(GooCanvasTableModel* castitem)
:
  Goocanvas::GroupModel((GooCanvasGroupModel*)(castitem))
{}


TableModel::~TableModel()
{}


TableModel::CppClassType TableModel::tablemodel_class_; // initialize static member

GType TableModel::get_type()
{
  return tablemodel_class_.init().get_type();
}


GType TableModel::get_base_type()
{
  return goo_canvas_table_model_get_type();
}


TableModel::TableModel()
:
  // Mark this class as non-derived to allow C++ vfuncs to be skipped.
  Glib::ObjectBase(0),
  Goocanvas::GroupModel(Glib::ConstructParams(tablemodel_class_.init()))
{
  

}

Glib::RefPtr<TableModel> TableModel::create()
{
  return Glib::RefPtr<TableModel>( new TableModel() );
}


#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<double> TableModel::property_row_spacing() 
{
  return Glib::PropertyProxy<double>(this, "row-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<double> TableModel::property_row_spacing() const
{
  return Glib::PropertyProxy_ReadOnly<double>(this, "row-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<double> TableModel::property_column_spacing() 
{
  return Glib::PropertyProxy<double>(this, "column-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<double> TableModel::property_column_spacing() const
{
  return Glib::PropertyProxy_ReadOnly<double>(this, "column-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> TableModel::property_homogeneous_rows() 
{
  return Glib::PropertyProxy<bool>(this, "homogeneous-rows");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> TableModel::property_homogeneous_rows() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "homogeneous-rows");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<bool> TableModel::property_homogeneous_columns() 
{
  return Glib::PropertyProxy<bool>(this, "homogeneous-columns");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<bool> TableModel::property_homogeneous_columns() const
{
  return Glib::PropertyProxy_ReadOnly<bool>(this, "homogeneous-columns");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<double> TableModel::property_x_border_spacing() 
{
  return Glib::PropertyProxy<double>(this, "x-border-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<double> TableModel::property_x_border_spacing() const
{
  return Glib::PropertyProxy_ReadOnly<double>(this, "x-border-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<double> TableModel::property_y_border_spacing() 
{
  return Glib::PropertyProxy<double>(this, "y-border-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<double> TableModel::property_y_border_spacing() const
{
  return Glib::PropertyProxy_ReadOnly<double>(this, "y-border-spacing");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<double> TableModel::property_vert_grid_line_width() 
{
  return Glib::PropertyProxy<double>(this, "vert-grid-line-width");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<double> TableModel::property_vert_grid_line_width() const
{
  return Glib::PropertyProxy_ReadOnly<double>(this, "vert-grid-line-width");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy<double> TableModel::property_horz_grid_line_width() 
{
  return Glib::PropertyProxy<double>(this, "horz-grid-line-width");
}
#endif //GLIBMM_PROPERTIES_ENABLED

#ifdef GLIBMM_PROPERTIES_ENABLED
Glib::PropertyProxy_ReadOnly<double> TableModel::property_horz_grid_line_width() const
{
  return Glib::PropertyProxy_ReadOnly<double>(this, "horz-grid-line-width");
}
#endif //GLIBMM_PROPERTIES_ENABLED


} // namespace Goocanvas


