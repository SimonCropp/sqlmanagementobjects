 ///////////////////////////////////////////////////////////////
 // Copyright (c) Microsoft.
 // Licensed under the MIT license.
 //
 // WARNING : DO NOT ATTEMPT TO MODIFY THIS FILE MANUALLY
 // 
 // This classes is autogenerated from schema_generic_collection.cs
 //
 ///////////////////////////////////////////////////////////////

using System;
using System.Data;
using System.Collections;
#pragma warning disable 1590,1591,1592,1573,1571,1570,1572,1587

#include "coll_macros.h"

namespace NAMESPACE_NAME
{

	///<summary>
	/// Strongly typed collection of MAPPED_TYPE objects
	/// Supports indexing objects by their Name and Schema properties
	///</summary>
	public SEALED_IMP class TOKEN_PASTE( MAPPED_TYPE, COLLECTION_SUFFIX) : SchemaCollectionBase
	{

		internal TOKEN_PASTE( MAPPED_TYPE, COLLECTION_SUFFIX)(SqlSmoObject parentInstance)  : base(parentInstance)
		{
		}

#ifdef PARENT
		public PARENT Parent
		{
			get
			{
				return this.ParentInstance as PARENT;
			}
		}
#endif

		public MAPPED_TYPE this[Int32 index]
		{
			get
			{ 
				return GetObjectByIndex(index) as MAPPED_TYPE;
			}
		}

		public MAPPED_TYPE this[KEY_TYPE name]
		{
			get
			{
                if (name == null)
                {
                    throw new ArgumentNullException("name cannot be null");
                }

		        return GetObjectByKey(new SchemaObjectKey(name, GetDefaultSchema())) as MAPPED_TYPE;
			}
		}

		public MAPPED_TYPE this[KEY_TYPE name, KEY_TYPE schema]
		{
			get
			{
                if (name == null)
                {
                    throw new ArgumentNullException("name cannot be null");
                }
                else if (schema == null)
                {
                    throw new ArgumentNullException("schema cannot be null");
                }

                return GetObjectByKey(new SchemaObjectKey(name, schema)) as MAPPED_TYPE;
			}
		}

		public void CopyTo(MAPPED_TYPE[] array, int index)
		{
			((ICollection)this).CopyTo(array, index);
		}

#ifdef ITEM_BY_ID
		public MAPPED_TYPE ItemById(int id)
		{
			return (MAPPED_TYPE)GetItemById(id);
		}
#endif

		protected override Type GetCollectionElementType()
		{
			return typeof(MAPPED_TYPE);
		}

		internal override SqlSmoObject GetCollectionElementInstance(ObjectKeyBase key, SqlSmoState state)
		{
			return new MAPPED_TYPE(this, key, state);
		}

		#ifdef REMOVE

			public void Remove(string name, string schema)
			{
                if (name == null)
                {
                    throw new ArgumentNullException("name cannot be null");
                }
                else if (schema == null)
                {
                    throw new ArgumentNullException("schema cannot be null");
                }

                this.Remove(new SchemaObjectKey(name, schema));
			}

			public void Remove(string name)
			{
                if (name == null)
                {
                    throw new ArgumentNullException("name cannot be null");
                }

                this.Remove(new SchemaObjectKey(name, GetDefaultSchema()));
			}

			public void Remove(MAPPED_TYPE MAPPED_TYPE_VAR)
			{
				if( null == MAPPED_TYPE_VAR )
					throw new FailedOperationException(ExceptionTemplates.RemoveCollection, this, new ArgumentNullException(STRINGER(MAPPED_TYPE_VAR)));
			
				RemoveObj(MAPPED_TYPE_VAR, new SchemaObjectKey(MAPPED_TYPE_VAR.Name, MAPPED_TYPE_VAR.Schema));
			}
#endif // REMOVE		

			public void Add(MAPPED_TYPE MAPPED_TYPE_VAR) 
			{
				if( null == MAPPED_TYPE_VAR )
					throw new FailedOperationException(ExceptionTemplates.AddCollection, this, new ArgumentNullException(STRINGER(MAPPED_TYPE_VAR)));
			
				AddImpl(MAPPED_TYPE_VAR);
			}

		internal SqlSmoObject GetObjectByName(string name)
		{
            if (name == null)
            {
                throw new ArgumentNullException("schema cannot be null");
            }

			return GetObjectByKey(new SchemaObjectKey(name, GetDefaultSchema()));
		}

	}
}
