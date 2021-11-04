/*
* ==============================================================================
*  Name        : xmlengnamespace.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Namespace node functions
*  Version     : %version: 2 %
*
*  Copyright © 2004-2006 Nokia. All rights reserved.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia. All rights are reserved. Copying, including 
*  reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia.
* ==============================================================================
*/

#ifndef XMLENGINE_NAMESPACE_H_INCLUDED
#define XMLENGINE_NAMESPACE_H_INCLUDED

#include "xmlengnode.h"

/**
 *   Represents existing namespace declaration in DOM tree <b>OR</b> namespace node returned
 *   in RXmlEngNodeSet as a result of some XPath expression. 
 *
 *   All elements and attributes may have a namespace instance associated.
 *   Once put in element, a namespace declaration (instance of TXmlEngNamespace) may be 
 *   referred to by all attributes and descentants of the element (unless
 *   prefix that this namespace-to-prefix binding uses is overriden somewhere below in the document tree)
 *
 *   <b>General rules of namespace handling:</b>
 *
 * - <b>NULL</b> prefix in namespace node means NO PREFIX. ""(empty string '\\0') can be used for specifying 
 *   absense of prefix when setting it, however <b>NULL</b> will be stored and returned.
 *
 * - <b>NULL</b> value of namespace URI is legal only with <b>NULL</b> prefix and only met in 
 *   undeclaration of namespace (<i>xmlns=""</i>). <b>""</b> (empty string) can be used too, however it 
 *   will be returned as <b>NULL</b>.
 *
 * - <b>NULL</b> or <b>""</b> namespace <b>URI</b> with non-<b>NULL</b> prefix is illegal acording to the XML specification.
 *
 * - Namespace of a element is <b>default</b> if it is associated with some namespace declaration with <b>NULL</b> prefix.
 *
 * - Elements are never associated with namespace undeclarations (<b>xmlns=""</b>), instead, such elements have no
 *   namespace declaration referred to. 
 *
 * - Attributes do not have <i>default</i> namespace. Even if it is effective at element scope,
 *   default namespace declaration is not applied to element's attributes (according to the XML specification)
 *
 * - Namespace of a node (element or attribute) is <b>undefined</b> if no namespace declaration is
 *   associated with it.
 *
 * - Node with <i>undefined</i> namespace is serialized as having no prefix. In general,
 *   DOM API handles the complexity of namespace declaration handling and creates neccessary
 *   namespace declarations and undeclares default namespace. However, some node-creation methods (e.g. TXmlEngElement::AddNewElementL()) 
 *   do not ensure that created node with undefined namespace (thus, without a prefix) will 
 *   actually treated after serialization as having some <i>default</i> namespace
 *
 *   @note
 *   Namespace nodes that are result of XPath expression have following restrictions:
 *       - they cannot be used as namespace definitions, because they are not part of
 *         the DOM tree, but copies of existing namespace definitions.
 *       - namespace prefix is not available because it is not mandated by DOM Level 3 XPath module API, 
 *         so in returned copies of DOM tree, namespaces prefix strings are not preserved 
 *         and Prefix() returns NULL.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngNamespace: public TXmlEngNode
{
  public:
    /**
     * Default constructor
     *
     * @since S60 v3.1
     */
	inline TXmlEngNamespace();

    /**
    /**
     * Get namespace URI
     *
     * @since S60 v3.1
     * @return Namespace URI string 
     * @note "" is never returned - it is replaced with NULL
     *
     * For TXmlEngNamespace(NULL) or namespace undeclaration (xmlns=""), which are
     * treatet as <i>undefined namespace</i> returns NULL,
     * otherwise result is not a NULL string and not a "" (empty string).
     */
    IMPORT_C TPtrC8 Uri() const;

    /**
     * Get namespace prefix. 
     *
     * @since S60 v3.1
     * @return prefix that is bound in the namespace declaration
     * or NULL string for default namespace or if no binding exist
     */
    IMPORT_C TPtrC8 Prefix() const;

    /**
     * Check if namespace is default.
     *
     * @since S60 v3.1
     * @return Whether it is a definition of default namespace
     *    TRUE  -- is a default namespace (no prefix)
     *    FALSE -- not a default namespace (bound to prefix) or empty TXmlEngNamespace(NULL) instance
     */
    IMPORT_C TBool IsDefault() const;

	/**
     * Check if namespace is undefined
	 *
     * @since S60 v3.1
     * @return Whether the namespace is undefined
     *
     * A node's namespace is undefined if no namespace declaration associated with it.
     * @note Same as TXmlEngNode::IsNull()
     */
    IMPORT_C TBool IsUndefined() const; 

protected:
    /**
     *   Workaround to avoid misuse of TXmlEngNode::NamespaceUri() method, which should not be
     *   applied to TXmlEngNamespace node. Since the name of the inherited method from TXmlEngNode
     *   is too similar to TXmlEngNamespace::Uri(), NamespaceUri() is disabled for direct
     *   use. 
     *   If NamespaceUri() is called on the TXmlEngNamespace object that is downcasted to TXmlEngNode, then
     *   NamespaceUri()'s result equals to result of Uri() method.
     *
     * @since S60 v3.1
     * @return NULL
     */
	inline TPtrC8 NamespaceUri();

protected:
    /**
     * Constructor
     *
     * @since S60 v3.1
     * @param aPtr Namespace pointer
     */
	inline TXmlEngNamespace(void* aPtr);

    friend class TXmlEngElement;
    friend class TXmlEngNode;
};

#include "xmlengnamespace.inl"

#endif /* XMLENGINE_NAMESPACE_H_INCLUDED */

